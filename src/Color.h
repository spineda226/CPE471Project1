#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
   public:
      Color() {};
      Color(int r, int g, int b);
      int getR() const { return r; }
      int getG() const { return g; }
      int getB() const { return b; }

   private:
      int r;
      int g;
      int b;
};

#endif
