#include "subspace.h"
#include "sfmlutil.h"
#include <iostream>

Subspace::Subspace(Vec pos, Vec size, sfmlutil* sfml_, bool canmove_) : sfml(sfml_) {
  count = 1;
  Rift r;
  r.tl = pos;
  r.br = pos+size;
  r.canmove = canmove_;
  members.push_back(r);

  sstexture.create(int(members[0].br.x-members[0].tl.x), int(members[0].br.y-members[0].tl.y));
  rect.setOutlineThickness(2.0);
	rect.setOutlineColor(sf::Color::White);
  rect.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, 0x80));

  anyhovered = false;
  picked = NULL;
}

void Subspace::add(Vec pos, bool canmove_) {
  count++;
  Rift r;
  r.tl = pos;
  r.br = pos+members[0].br-members[0].tl;
  r.canmove = canmove_;
  members.push_back(r);
}

void Subspace::add(Vec pos, Vec size, bool canmove_) {
  count++;
  Rift r;
  r.tl = pos;
  r.br = pos+size;
  r.canmove = canmove_;
  members.push_back(r);
}

bool Subspace::ssaabb(Vec tl1, Vec br1, Vec tl2, Vec br2) {
  if (aabb(tl1, br1, tl2, br2)) {return true;}
  for (int i = 0; i < members.size(); i++) {
    if (aabb(tl2, br2, members[i].tl, members[i].br)) {
      for (int j = 0; j < members.size(); j++) {
        Vec tl2crop = { std::max(tl2.x, members[i].tl.x), std::max(tl2.y, members[i].tl.y) };
        Vec br2crop = { std::min(br2.x, members[i].br.x), std::min(br2.y, members[i].br.y) };
        tl2crop += members[j].tl-members[i].tl;
        br2crop += members[j].tl-members[i].tl;
        if (j != i && aabb(tl1, br1, tl2crop, br2crop)) {return true;}
      }
    }
  }
  return false;
}

void Subspace::step() {
  anyhovered = false;
  for (int i = 0; i < members.size(); i++) {
    members[i].hovered = false;
    if (point_in_rectangle(sfml->mouse, members[i].tl, members[i].br) && !picked) {
      members[i].hovered = true; anyhovered = true;
      if (sfml->is_mouse_pressed(sf::Mouse::Button::Left)) {
        picked = &members[i];
      }
    }
  }

  if (picked) {
    picked->tl += sfml->mouse-sfml->mouse_prev;
    picked->br += sfml->mouse-sfml->mouse_prev;
    if (sfml->is_mouse_released(sf::Mouse::Button::Left))
      picked = NULL;
  }
}

void Subspace::begin_draw() {
  sstexture.clear(sf::Color::Transparent);
}

void Subspace::draw() {
  sstexture.display();
  rect.setOutlineColor(anyhovered ? sf::Color::Yellow : sf::Color::White);
  for (int i = 0; i < members.size(); i++) {
    rect.setPosition(members[i].tl.x, members[i].tl.y);
    rect.setOutlineThickness(members[i].hovered ? 4.0 : 2.0);
    rect.setSize(to_sfvec2f(members[i].br-members[i].tl));
    rect.setTexture(&sstexture.getTexture());
    sfml->window.draw(rect);
  }
}

void Subspace::end_draw() {

}

void Subspace::draw_to(sf::Drawable& drawable, sf::Transformable* transformable) {
  for (int i = 0; i < members.size(); i++) {
    transformable->move(-members[i].tl.x, -members[i].tl.y);
    sstexture.draw(drawable);
    transformable->move(members[i].tl.x, members[i].tl.y);
  }
}
