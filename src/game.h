#pragma once

#define SDL_MAIN_HANDLED
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

#include "vec.h"
#include "graphics.h"
#include "input.h"

class Entity;

class Game { // this is bad software architecture but who cares
protected:
	bool quit;
	bool restart;

	std::vector<std::shared_ptr<Entity>> entities;

	void on_game_start(); // game starts and restarts here
	void on_game_loop(); // what happens in each frame from begin step to draw end,
						// cycles through object pool and calls their frame functions

public:
	Input* input;
	Graphics* graphics;
	
	Game(); // get input and graphics ready
	~Game(); // flush everything

	void run();

	void game_end();
	void game_restart();

	Entity* instance_add(std::shared_ptr<Entity> inst);
	void instance_remove(Entity* inst);
};

class Entity {
public:
	Game* game;
	Input* input;
	Graphics* graphics;

	Vec pos; // top-left of bb
	Vec pos_previous;
	Vec pos_start;
	Vec size;

	Vec speed;

	std::string sprite;
	int subimg;
	float anim_speed;
	float subimgf;
	float xscale;
	float yscale;
	float angle;
	bool use_sprite_size;
	SDL_Color color;

	Entity(); //must set name and initialize()
	void initialize(); // mandatory to call before anything else in constructor

	// t functions called internally
	void t_begin_step(); // calls create, destroy if needed, sets pos_previous
	void t_step(); // calls virtual counterpart, then moves pos by speed, and other such builtin functions
	void t_end_step();

	void t_begin_draw();
	void t_draw();
	void t_end_draw();

	void instance_destroy();
	std::string get_name();

	virtual void on_game_start();
	virtual void on_game_end();

protected:
	std::string name; // name of the class, same as GM's object_index in a way, different for each entity class
	bool created;
	bool destroyed;

	virtual void on_create();

	virtual void on_begin_step();
	virtual void on_step();
	virtual void on_end_step();

	virtual void on_begin_draw();
	virtual void on_draw(); // draw_self included here unless overriden
	virtual void on_end_draw();

	virtual void on_destroy();
	
};