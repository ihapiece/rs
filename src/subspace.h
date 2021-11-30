#pragma once
#include <vector>
#include "vec.h"
#include "sfmlutil.h"

struct Rift {
  Vec tl;
  Vec br;
  bool canmove;
  bool hovered;
};

class Subspace {
  /*rules:
  - first member should be the largest, for texture reasons
  */
public:
  int count;
  std::vector<Rift> members;
  sf::RenderTexture sstexture;
  sf::RectangleShape rect; //sfml please stop frocing me to use oop
  sfmlutil* sfml;

  bool anyhovered;

  Subspace(Vec pos, Vec size, sfmlutil* sfml_, bool canmove_=true);
  void add(Vec pos, bool canmove_=true);
  void add(Vec pos, Vec size, bool canmove_=true);
  bool ssaabb(Vec tl1, Vec br1, Vec tl2, Vec br2); //returns whether two rectangles collide within this ss
  void step();
  void begin_draw(); //before other stuff draw to it
  void draw();
  void end_draw();
  void draw_to(sf::Drawable& drawable, sf::Transformable* transformable);
};
