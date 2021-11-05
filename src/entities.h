#pragma once
#include "game.h"

class Player : public Entity {
  public:
  Player();

  protected:
  Entity* ground;
	unsigned char coyote;
	float gaccel;
	float friction;
	float maxspeed;
	float aaccel;
	float airres;

  virtual void on_create();
  virtual void on_step();
  virtual void on_end_step();
  virtual void on_begin_draw();
  virtual void on_draw();
  virtual void on_destroy();
};

class Block : public Entity {
public:
	Block();
	virtual void on_end_draw();
};

class WavingBlock : public Entity {
public:
	float t;
  float tsp;
	float basey;
	float basex;
	WavingBlock();

	virtual void on_create();

	virtual void on_step();

	virtual void on_end_draw();
};
