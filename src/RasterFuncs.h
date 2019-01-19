#ifndef _RASTERFUNCS_H_
#define _RASTERFUNCS_H_

#include "Triangle.h"

float calculateC(int width, int height);
float calculateD(int width, int height);
float calculateE(int width, int height);
float calculateF(int width, int height);
unsigned int calculateRed(double alpha, double beta, double gamma, Triangle *t);
unsigned int calculateGreen(double alpha, double beta, double gamma, Triangle *t);
unsigned int calculateBlue(double alpha, double beta, double gamma, Triangle *t);
int w2pX(float xw, float c, float d);
int w2pY(float yw, float e, float f);
int w2cZ(float zw);
float distance(int x1, int y1, int x2, int y2);
double getCurZ(double alpha, double beta, double gamma, Triangle *t);
float getMaxDistance(int width, int height, int binnedX, int binnedY);
int distanceToColor(float curDistance, float maxDistance);

#endif
