#include "Triangle.h"
#include <algorithm>
using namespace std;

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3):
   v1(v1), v2(v2), v3(v3), box(createBound(v1,v2,v3))
{
}

// Calculates the bouning box for the triangle
Box
Triangle::createBound(Vertex v1, Vertex v2, Vertex v3)
{
   float minX = std::min(std::min(v1.getP().getX(), v2.getP().getX()), v3.getP().getX());
   float minY = min(min(v1.getP().getY(), v2.getP().getY()), v3.getP().getY());
   float maxX = max(max(v1.getP().getX(), v2.getP().getX()), v3.getP().getX());
   float maxY = max(max(v1.getP().getY(), v2.getP().getY()), v3.getP().getY());
   Point botLeft(minX, minY, 0);
   Point topRight(maxX, maxY, 0);
   Box bound(botLeft, topRight);
   return bound;
}

double
Triangle::getArea(Point a, Point b, Point c)
{
   return 0.5*((a.getX()-c.getX())*(b.getY()-c.getY()) -
	       (b.getX()-c.getX())*(a.getY()-c.getY()));
}

bool
inTriangle(double alpha, double beta, double gamma)
{
   float epsilon = 0.001;
   return ((alpha >= 0-epsilon) && (alpha <= 1+epsilon) &&
           (beta >= 0-epsilon) && (beta <= 1+epsilon) &&
           (gamma >= 0-epsilon) && (gamma <= 1+epsilon));
}
