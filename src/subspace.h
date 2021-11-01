#pragma once
#include <vector>
#include "vec.h"
#include "sfmlutil.h"

class Subspace {
  /*a few rules:
  - first member should be the largest, for texture reasons
  */
public:
  int count;
  std::vector<Vec> tl; // top left position of each member
  std::vector<Vec> br; // bottom right position of each member
  sf::RenderTexture sstexture;
  sf::RectangleShape rect; //sfml please stop frocing me to use oop
  sfmlutil* sfml;

  Subspace(Vec pos, Vec size, sfmlutil* sfml_);
  void add(Vec pos);
  void add(Vec pos, Vec size);
  bool ssaabb(Vec tl1, Vec br1, Vec tl2, Vec br2); //returns whether two rectangles collide, in subspaces or not
  void begin_draw(); //before other stuff draw to it
  void draw();
  void end_draw();
  void draw_to(sf::Drawable& drawable, sf::Transformable* transformable);
};
