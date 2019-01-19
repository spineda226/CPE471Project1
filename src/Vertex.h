#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "Point.h"
#include "Color.h"

class Vertex
{
   public:
      Vertex() {};
      Vertex(Point p, Color c);
      Point getP() const { return p; };
      Color getC() const { return color; };

   private:
      Point p;
      Color color;
};

#endif
