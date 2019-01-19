#ifndef _POINT_H_
#define _POINT_H_

class Point
{
   public:
      Point() {};
      Point(float x, float y, float z);
      float getX() const { return x; }
      float getY() const { return y; }
      float getZ() const { return z; }

   private:
      float x;
      float y;
      float z;
};

#endif
