#include "subspace.h"

Subspace::Subspace(Vec pos, Vec size, Graphics* g) : graphics(g) {
  count = 1;
  tl.push_back(pos);
  br.push_back(pos+size);
  subspace_texture = SDL_CreateTexture(graphics->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, int(size.x), int(size.y));
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
  if (count > 1) {
    for (unsigned int i = 1; i < count; i++) {
      // i hope to whatever being looking from the heavens that this works symmetrically

      if (aabb(tl2, br2, tl[i], br[i])) {
        if (aabb(tl1, br1, Vec(std::max(tl2.x-tl[0].x+tl[i].x, tl[i].x), std::max(tl2.y-tl[0].y+tl[i].y, tl[i].y)),
                           Vec(std::min(br2.x-tl[0].x+tl[i].x, br[i].x), std::min(br2.y-tl[0].y+tl[i].y, br[i].y)))) {
          return true;
        }
      }
    }
  }
  return false;
}

void Subspace::draw() {
  graphics->draw_set_color(0xFF, 0x00, 0x00, 0x00);
  for (unsigned int i = 0; i < count; i++) {
    graphics->draw_texture(subspace_texture, tl[i], br[i]-tl[i], br[i]-tl[i]);
    graphics->draw_rectangle(tl[i], br[i], true);
  }
}
