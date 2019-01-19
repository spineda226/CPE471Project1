#ifndef _BOX_H_
#define _BOX_H_

#include "Point.h"

class Box
{
   public:
      Box(Point botLeft, Point topRight);
      Point getBotLeft() const { return botLeft; }
      Point getTopRight() const { return topRight; }

   private:
      Point botLeft;
      Point topRight;
};

#endif
