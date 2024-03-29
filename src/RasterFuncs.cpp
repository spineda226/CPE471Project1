#include "RasterFuncs.h"
#include <iostream>
#include <math.h>

// calculate x scale
float calculateC(int width, int height)
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

// get current z using barycentric coordinates
double getCurZ(double alpha, double beta, double gamma, Triangle *t)
{
   return alpha*t->getV1().getP().getZ() +
          beta*t->getV2().getP().getZ() +
          gamma*t->getV3().getP().getZ();
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
   return distance(0, 0, maxDistanceX, maxDistanceY);
}

// calculate distance from a location
float distance(int x1, int y1, int x2, int y2)
{
   return sqrt((x2-x1)*(x2-x1) + (float)(y2-y1)*(y2-y1));
}

// return ratio of current distance to max distance
float binnedRatio(float curDistance, float maxDistance)
{
   float ratio = (curDistance/maxDistance);
   float bin = 0;
   if ((ratio >= 0) && (ratio <= 0.1))
      bin = 0.1;
   else if (ratio <= 0.2)
      bin = 0.2;
   else if (ratio <= 0.3)
      bin = 0.3;
   else if (ratio <= 0.4)
      bin = 0.4;
   else if (ratio <= 0.5)
      bin = 0.5;
   else if (ratio <= 0.6)
      bin = 0.6;
   else if (ratio <= 0.7)
      bin = 0.7;
   else if (ratio <= 0.8)
      bin = 0.8;
   else if (ratio <= 0.9)
      bin = 0.9;
   else
      bin = 1;
   return bin;
}
