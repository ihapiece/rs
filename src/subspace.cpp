#include "subspace.h"
#include "sfmlutil.h"
#include <iostream>

Subspace::Subspace(Vec pos, Vec size, sfmlutil* sfml_) : sfml(sfml_) {
  count = 1;
  tl.push_back(pos);
  br.push_back(pos+size);
  sstexture.create(int(br[0].x-tl[0].x), int(br[0].y-tl[0].y));
  rect.setOutlineThickness(2.0);
	rect.setOutlineColor(sf::Color::White);
  rect.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, 0x90));
}

void Subspace::add(Vec pos) {
  count++;
  tl.push_back(pos);
  br.push_back(pos+br[0]-tl[0]);
}

void Subspace::add(Vec pos, Vec size) {
  count++;
  tl.push_back(pos);
  br.push_back(pos+size);
}

bool Subspace::ssaabb(Vec tl1, Vec br1, Vec tl2, Vec br2) {
  if (aabb(tl1, br1, tl2, br2)) {return true;}
  for (int i = 0; i < count; i++) {
    if (aabb(tl2, br2, tl[i], br[i])) {
      for (int j = 0; j < count; j++) {
        Vec tl2crop = { std::max(tl2.x, tl[i].x), std::max(tl2.y, tl[i].y) };
        Vec br2crop = { std::min(br2.x, br[i].x), std::min(br2.y, br[i].y) };
        tl2crop += tl[j]-tl[i];
        br2crop += tl[j]-tl[i];
        if (j != i && aabb(tl1, br1, tl2crop, br2crop)) {return true;}
      }
    }
  }
  return false;
}

void Subspace::begin_draw() {
  sstexture.clear(sf::Color(0, 0, 0, 0));
}

void Subspace::draw() {
  sstexture.display();
}

void Subspace::end_draw() {
  for (int i = 0; i < tl.size(); i++) {
    rect.setPosition(tl[i].x, tl[i].y);
    rect.setSize(to_sfvec2f(br[i]-tl[i]));
    rect.setTexture(&sstexture.getTexture());
    sfml->window.draw(rect);
  }
}

void Subspace::draw_to(sf::Drawable& drawable, sf::Transformable* transformable) {
  for (int i = 0; i < tl.size(); i++) {
    transformable->move(-tl[i].x, -tl[i].y);
    sstexture.draw(drawable);
    transformable->move(tl[i].x, tl[i].y);
  }
}
