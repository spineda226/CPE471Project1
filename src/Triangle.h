#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vertex.h"
#include "Box.h"

class Triangle
{
   public:
      Triangle(Vertex v1, Vertex v2, Vertex v3);
      Box createBound(Vertex v1, Vertex  v2, Vertex  v3); 
      static double getArea(Point a, Point b, Point c);
      Vertex getV1() const { return v1; }
      Vertex getV2() const { return v2; }
      Vertex getV3() const { return v3; }
      Box getBox() const { return box; }

   private:
      Vertex v1;
      Vertex v2;
      Vertex v3;
      Box box;
};

bool inTriangle(double alpha, double beta, double gamma);

#endif
