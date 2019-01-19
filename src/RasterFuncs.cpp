#include "RasterFuncs.h"
#include <iostream>
#include <math.h>

// calculate x scale
float calculateC(int width, int height)
{
   float left, right;
   if (width > height)
   {
      left = -width/(float)height;
      right = width/(float)height;
   }
   else
   {
      left = -1.0;
      right = 1.0;
   }
   std::cout << "width: " << width << " " << right << " " << left << " C: " << (width-1)/(right-left) << std::endl;
   return (width-1.0)/(right-left);
}

// calculate x shift
float calculateD(int width, int height)
{
   float left, right;
   if (width > height)
   {
      left = -1.0*width/(float)height;
      right = width/(float)height;
   }
   else
   {
      left = -1.0;
      right = 1.0;
   }
   std::cout << "width: " << width << " " << right << " " << left << " D: " << (1-width)*left/(right-left) << std::endl;
   return (1.0-width)*left/(right-left);
}

// calculate y scale
float calculateE(int width, int height)
{
   float bottom, top;
   if (width > height)
   {
      bottom = -1.0;
      top = 1.0;
   }
   else
   {
      bottom = -1.0*height/(float)width;
      top = height/(float)width;
   }
   std::cout << "height: " << height << " " << bottom << " " << top << " E: " << (height-1)/(top-bottom) << std::endl;
   return (height-1.0)/(top-bottom);
}

// calculate y shift
float calculateF(int width, int height)
{
   float bottom, top;
   if (width > height)
   {
      bottom = -1.0;
      top = 1.0;
   }
   else
   {
      bottom = -1.0*height/(float)width;
      top = height/(float)width;
   }
   return (1.0-height)*bottom/(top-bottom);
}

// calculate r from barrycentric coordinates
unsigned int calculateRed(double alpha, double beta, double gamma, Triangle *t)
{
   return alpha*t->getV1().getC().getR() + 
          beta*t->getV2().getC().getR() + 
          gamma*t->getV3().getC().getR();
}

// calculate g from barrycentric coordinates
unsigned int calculateGreen(double alpha, double beta, double gamma, Triangle *t)
{
   return alpha*t->getV1().getC().getG() +
          beta*t->getV2().getC().getG() +
          gamma*t->getV3().getC().getG();
}

// calculate b from barrycentric coordinates
unsigned int calculateBlue(double alpha, double beta, double gamma, Triangle *t)
{
   return alpha*t->getV1().getC().getB() +
          beta*t->getV2().getC().getB() +
          gamma*t->getV3().getC().getB();
}

// convert x-world to x-pixel
int w2pX(float xw, float c, float d)
{
   return c*xw+d;
}

// convert y-world to y-pixel
int w2pY(float yw, float e, float f)
{
   return e*yw+f;
}

// convert z-world to color (0-255)
int w2cZ(float zw)
{
   return (zw+1.0)*127.5;
}

// calculate max distance from binned_x and binned_y
float getMaxDistance(int width, int height, int binnedX, int binnedY)
{
   float maxDistanceX, maxDistanceY;
   if (binnedX > (width/2))
      maxDistanceX = binnedX;
   else
      maxDistanceX = (width-binnedX);
   if (binnedY > (height/2))
      maxDistanceY = binnedY;
   else
      maxDistanceY = (height-binnedY);
   //std::cout << "Max X: " << maxDistanceX << " " << maxDistanceY << std::endl;
   return distance(0, 0, maxDistanceX, maxDistanceY);
}

// calculate distance from a location
float distance(int x1, int y1, int x2, int y2)
{
   return sqrt((x2-x1)*(x2-x1) + (float)(y2-y1)*(y2-y1));
}

// convert distance (0-maxDistance) to color (0-255)
int distanceToColor(float curDistance, float maxDistance)
{
   float colorVal = (curDistance/maxDistance)*255;
   if (colorVal > 255) // check for floating error
      colorVal = 255;
   return colorVal;
}
