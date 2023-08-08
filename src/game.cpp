#include "game.h"

Game::Game(sfmlutil* s_) : sfml(s_) {
	zoom = 1;
	current_room = "nothing";
}

Game::~Game() {

}

void Game::on_game_start() {
	for (auto i : entities) {i->on_game_start();}
	editor.sfml = sfml;
	editor.game = this;
	editor.start();
}

void Game::on_game_loop() {
	for (auto i : subspaces) {i->step();}
	for (auto i : entities) {i->t_begin_step();}
	for (auto i : entities) {i->t_step();}
	editor.update();
	for (auto i : entities) {i->t_end_step();}
}

void Game::on_game_draw() {
	camera.setSize(sfml->window.getSize().x, sfml->window.getSize().y);
	camera.zoom(zoom);
	sfml->window.setView(camera);
	for (auto i : subspaces) {i->begin_draw();}
	for (auto i : entities) {i->t_begin_draw();}
	for (auto i : entities) {i->t_draw();}
	for (auto i : subspaces) {i->draw();}
	for (auto i : entities) {i->t_end_draw();}
	for (auto i : subspaces) {i->end_draw();}
	editor.draw();
}

void Game::game_end() {
	sfml->window.close();
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

Subspace* Game::subspace_add(Vec pos, Vec size, bool canmove_) {
	auto ss = std::make_shared<Subspace>(pos, size, sfml);
	subspaces.push_back(ss);
	return ss.get();
}

void Game::subspace_remove(Subspace* ss) {
	subspaces.erase(std::find_if(subspaces.begin(), subspaces.end(), [&ss](auto i) {return i.get() == ss;}));
}

bool Game::ssaabb(Vec tl1, Vec br1, Vec tl2, Vec br2) {
	for (auto i : subspaces) {
		if (i->ssaabb(tl1, br1, tl2, br2)) {return true;}
	}
	return false;
}

void Game::draw_to_ss(sf::Drawable& drawable, sf::Transformable* transformable) {
	for (auto i : subspaces) {
		i->draw_to(drawable, transformable);
	}
}
