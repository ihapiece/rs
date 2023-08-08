#pragma once
#include "sfmlutil.h"

class Game;

enum EditorMode { nothing, blockedit };

class Editor {
public:
  sfmlutil* sfml;
  Game* game;

  bool open;
  EditorMode mode;
  Vec topleft;

  sf::Text hud;

  void start();
  void update();
  void draw();
};