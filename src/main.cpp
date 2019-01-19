/* Release code for program 1 CPE 471 Fall 2016 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Image.h"

#include "Point.h"
#include "Vertex.h"
#include "Color.h"
#include "Box.h"
#include "Triangle.h"
#include "RasterFuncs.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int g_width, g_height;

/*
   Helper function you will want all quarter
   Given a vector of shapes which has already been read from an obj file
   resize all vertices to the range [-1, 1]
 */
void resize_obj(std::vector<tinyobj::shape_t> &shapes){
   float minX, minY, minZ;
   float maxX, maxY, maxZ;
   float scaleX, scaleY, scaleZ;
   float shiftX, shiftY, shiftZ;
   float epsilon = 0.001;

   minX = minY = minZ = 1.1754E+38F;
   maxX = maxY = maxZ = -1.1754E+38F;

   //Go through all vertices to determine min and max of each dimension
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         if(shapes[i].mesh.positions[3*v+0] < minX) minX = shapes[i].mesh.positions[3*v+0];
         if(shapes[i].mesh.positions[3*v+0] > maxX) maxX = shapes[i].mesh.positions[3*v+0];

         if(shapes[i].mesh.positions[3*v+1] < minY) minY = shapes[i].mesh.positions[3*v+1];
         if(shapes[i].mesh.positions[3*v+1] > maxY) maxY = shapes[i].mesh.positions[3*v+1];

         if(shapes[i].mesh.positions[3*v+2] < minZ) minZ = shapes[i].mesh.positions[3*v+2];
         if(shapes[i].mesh.positions[3*v+2] > maxZ) maxZ = shapes[i].mesh.positions[3*v+2];
      }
   }

   //From min and max compute necessary scale and shift for each dimension
   float maxExtent, xExtent, yExtent, zExtent;
   xExtent = maxX-minX;
   yExtent = maxY-minY;
   zExtent = maxZ-minZ;
   if (xExtent >= yExtent && xExtent >= zExtent) {
      maxExtent = xExtent;
   }
   if (yExtent >= xExtent && yExtent >= zExtent) {
      maxExtent = yExtent;
   }
   if (zExtent >= xExtent && zExtent >= yExtent) {
      maxExtent = zExtent;
   }
   scaleX = 2.0 /maxExtent;
   shiftX = minX + (xExtent/ 2.0);
   scaleY = 2.0 / maxExtent;
   shiftY = minY + (yExtent / 2.0);
   scaleZ = 2.0/ maxExtent;
   shiftZ = minZ + (zExtent)/2.0;

   //Go through all verticies shift and scale them
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         shapes[i].mesh.positions[3*v+0] = (shapes[i].mesh.positions[3*v+0] - shiftX) * scaleX;
         assert(shapes[i].mesh.positions[3*v+0] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+0] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+1] = (shapes[i].mesh.positions[3*v+1] - shiftY) * scaleY;
         assert(shapes[i].mesh.positions[3*v+1] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+1] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+2] = (shapes[i].mesh.positions[3*v+2] - shiftZ) * scaleZ;
         assert(shapes[i].mesh.positions[3*v+2] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+2] <= 1.0 + epsilon);
      }
   }
}


int main(int argc, char **argv)
{
   if(argc != 6) 
   {
      cout << "Usage: ./raster meshfile imagefile width height mode" << endl;
      return 0;
   }

   // OBJ filename
   string meshName(argv[1]);
   string imgName(argv[2]);
   
   //set g_width and g_height appropriately!
   g_width = atoi(argv[3]);
   g_height = atoi(argv[4]);

   // Coloring mode
   int mode = atoi(argv[5]);
   const int BINNED_X = g_width*0.75;
   const int BINNED_Y = g_height*0.75;

   //create an image
   auto image = make_shared<Image>(g_width, g_height);
   // Create z-buffer
   vector<float> zbuff;

   // triangle buffer
   vector<unsigned int> triBuf;
   // position buffer
   vector<float> posBuf;
   // Some obj files contain material information.
   // We'll ignore them for this assignment.
   vector<tinyobj::shape_t> shapes; // geometry
   vector<tinyobj::material_t> objMaterials; // material
   string errStr;
	
   bool rc = tinyobj::LoadObj(shapes, objMaterials, errStr, meshName.c_str());
   /* error checking on read */
   if(!rc) 
   {
      cerr << errStr << endl;
   } 
   else 
   {
      //keep this code to resize your object to be within -1 -> 1
      resize_obj(shapes);
      posBuf = shapes[0].mesh.positions;
      triBuf = shapes[0].mesh.indices;
   }
   int numVertices = posBuf.size()/3;
   int numTriangles = triBuf.size()/3;
   cout << "Number of vertices: " << numVertices << endl;
   cout << "Number of triangles: " << numTriangles << endl;
   
   //TODO add code to iterate through each triangle and rasterize it 
   Vertex vertices[3];
   int index;
   float c, d, e, f, maxDistance;
   c = calculateC(g_width, g_height);
   d = calculateD(g_width, g_height);
   e = calculateE(g_width, g_height);
   f = calculateF(g_width, g_height);
   maxDistance = getMaxDistance(g_width, g_height, BINNED_X, BINNED_Y); // for mode 2
   // Initialize zbuff to very small number
   for (int x = 0; x < g_width; ++x)
      for (int y = 0; y < g_height; ++y)
         zbuff.push_back(-1.1754E+38F);
   for (int i = 0; i < numTriangles; ++i) // for all faces
   {
      for (int j = 0; j < 3; ++j) // read three vertices in (with a color for each)
      {
         index = triBuf[3*i+j];
         // convert x and y to pixel coordinates, leave z as depth
         Point p(w2pX(posBuf[3*index], c, d), w2pY(posBuf[3*index+1], e, f), posBuf[3*index+2]);
         if (mode == 1) // color by depth
         {
            vertices[j] = Vertex(p, Color(0, w2cZ(p.getZ()), 0));
         }
         else // color by binned distance
         {
            float curDistance = distance(p.getX(), p.getY(), BINNED_X, BINNED_Y);
            unsigned char r = distanceToColor(curDistance, maxDistance);
            vertices[j] = Vertex(p, Color(0, r, 255-r));
         }
      }
      
      Triangle t(vertices[0], vertices[1], vertices[2]); // create triangle and bounding box
      double totalArea = Triangle::getArea(t.getV2().getP(), t.getV3().getP(), t.getV1().getP());
      Point botCorner(t.getBox().getBotLeft());
      Point topCorner(t.getBox().getTopRight());
      for (int y = botCorner.getY(); y <= topCorner.getY(); ++y) // iterate through bounding box
      {
         for (int x = botCorner.getX(); x <= topCorner.getX(); ++x)
         {
            Point temp(x, y, 0);
            double beta = Triangle::getArea(t.getV1().getP(), temp, t.getV3().getP())/totalArea;
            double gamma = Triangle::getArea(t.getV2().getP(), temp, t.getV1().getP())/totalArea;
	    double alpha = 1 - beta - gamma;
            if (inTriangle(alpha, beta, gamma)) // check if pixel is inside triangle
            {
               double curZ = getCurZ(alpha, beta, gamma, &t);
               if (((mode == 1) && (zbuff[g_width*y+x] < curZ)) || (mode == 2))
               {
                  image->setPixel(x, y, calculateRed(alpha, beta, gamma, &t),
                                        calculateGreen(alpha, beta, gamma, &t),
                                        calculateBlue(alpha, beta, gamma, &t));
                  if (mode == 1)
                     zbuff[g_width*y+x] = curZ;
               }
            }
         }
      }
   }   
   //write out the image
   image->writeToFile(imgName);
   return 0;
}
