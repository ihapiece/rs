#include "game.h"

Game::Game(sfmlutil* s_) : sfml(s_) {
	zoom = 1;
}

Game::~Game() {
	delete subspace; // temporary, will make some entity control subspaces soon
}

void Game::on_game_start() {
	subspace = new Subspace(Vec(400, 320), Vec(140, 100));
	subspace->add(Vec(100, 340));
	subspace->add(Vec(160, 300));

	for (auto i : entities) {i->on_game_start();}
}

void Game::on_game_loop() {
	for (auto i : entities) {i->t_begin_step();}
	for (auto i : entities) {i->t_step();}
	for (auto i : entities) {i->t_end_step();}

	camera.setSize(sfml->window.getSize().x, sfml->window.getSize().y);
	camera.zoom(zoom);
	sfml->window.setView(camera);
}

void Game::on_game_draw() {
	for (auto i : entities) {i->t_begin_draw();}
	subspace->draw();
	for (auto i : entities) {i->t_draw();}
	for (auto i : entities) {i->t_end_draw();}
}

void Game::game_end() {
	*quit = true;
}

Entity* Game::instance_add(std::shared_ptr<Entity> inst) {
	entities.emplace_back(inst);
	inst->game = this;
	inst->sfml = sfml;
	return inst.get();
}

void Game::instance_remove(Entity* inst) {
	entities.erase(std::find_if(entities.begin(), entities.end(), [&inst](auto i) {return i.get() == inst;} ));
}
