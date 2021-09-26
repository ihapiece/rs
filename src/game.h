#pragma once

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>

#include "sfmlutil.h"
#include "vec.h"
#include "subspace.h"

class Entity;

class Game { // this is bad software architecture but who cares
protected:
	bool* quit;

public:
	sfmlutil* sfml;
	sf::View camera;
	float zoom;
	std::vector<std::shared_ptr<Entity>> entities;
	Subspace* subspace;

	Game(sfmlutil* s_); // get input and graphics ready
	~Game(); // flush everything

	void run();
	void on_game_start();
	void on_game_loop();
	void on_game_draw();

	void game_end();

	Entity* instance_add(std::shared_ptr<Entity> inst);
	void instance_remove(Entity* inst);
};

class Entity {
public:
	Game* game;
	sfmlutil* sfml;

	Vec pos; // center of sprite
	Vec pos_previous;
	Vec pos_start;
	Vec btl; // top left relative to pos
	Vec bbr; // bottom right relative to pos
	Vec speed;
	bool solid;
	bool moves;

	sf::RectangleShape bshape;

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
	std::string name;
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

	Entity* meeting_solid(Vec pos_);
	bool meeting_entity(Vec pos_, Entity* i);
};
