#include "subspace.h"
#include <iostream>

Subspace::Subspace(Vec pos, Vec size, Graphics* g) : graphics(g) {
  count = 1;
  tl.push_back(pos);
  br.push_back(pos+size);
}

void Subspace::add(Vec pos) {
  count++;
  tl.push_back(pos);
  br.push_back(pos+br[0]-tl[0]);
}

void Subspace::add(Vec pos, Vec size) {
  count++;
  tl.push_back(pos);
  tl.push_back(pos+size);
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
        graphics->draw_set_color(0x01, 0xff, 0x01, 0xff);
        graphics->draw_rectangle(tl2crop, br2crop, true);
        if (j != i && aabb(tl1, br1, tl2crop, br2crop)) {return true;}
      }
    }
  }
  return false;
}

void Subspace::draw() {
  graphics->draw_set_color(0xFF, 0x00, 0x00, 0x00);
  for (unsigned int i = 0; i < count; i++) {
    graphics->draw_rectangle(tl[i], br[i], true);
  }
}
