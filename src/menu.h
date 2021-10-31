#pragma once
#include "game.h"

class Menu {
public:
  sfmlutil* sfml;
  Game* game;

  bool open;

  int submenu;
  int selection;
  std::vector<std::string> mainmenu;
  int charsize;

  sf::Clock clock_opened;
  float entrance;
  float cursory;
  int width;
  float slope;

  sf::ConvexShape cursor;
  sf::RenderStates whitedifference;
  sf::RenderStates bluemultiply;
  sf::RectangleShape dark;
  sf::VertexArray menubg;
  sf::Text text;

  Menu(sfmlutil* s_);

  void update();
  void draw();
};
