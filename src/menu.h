#pragma once
#include "game.h"

class Menu {
public:
  sfmlutil* sfml;
  Game* game;

  int submenu;
  int selection;
  std::vector<std::string> mainmenu;

  float entrance;
  float cursory;

  Menu(sfmlutil* s_);

  void update();
  void draw();
};
