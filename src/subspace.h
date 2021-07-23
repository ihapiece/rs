#pragma once
#include <vector>
#include "vec.h"
#include "graphics.h"

class Subspace {
public:
  Graphics* graphics;
  int count;
  std::vector<Vec> tl; // top left position of each member
  std::vector<Vec> br; // bottom right position of each member

  Subspace(Vec pos, Vec size, Graphics* g);
  void add(Vec pos);
  void add(Vec pos, Vec size);
  bool ssaabb(Vec tl1, Vec br1, Vec tl2, Vec br2); //returns whether two rectangles collide, in subspaces or not
  void draw(); // draw the texture
};
