#include "game.h"

Game::Game() {
	input = new Input(&quit);
	graphics = new Graphics;
	input->graphics = graphics;
	quit = false;
	restart = false;
}

Game::~Game() {
	delete input;
	delete graphics;
}

void Game::on_game_start() {
	for (auto i : entities) {i->on_game_start();}
}

void Game::on_game_loop() {
	input->update();

	if (input->keyboard_check_pressed(SDLK_F4)) {
		graphics->window_toggle_fullscreen();
	}

	for (auto i : entities) {i->t_begin_step();}
	for (auto i : entities) {i->t_step();}
	for (auto i : entities) {i->t_end_step();}

	graphics->draw_set_color(0x00, 0x00, 0x00, 0xFF);
	graphics->draw_clear();

	for (auto i : entities) {i->t_begin_draw();}
	for (auto i : entities) {i->t_draw();}
	for (auto i : entities) {i->t_end_draw();}

	SDL_Delay(1000/60);
	graphics->draw_flip();
}

void Game::run() {
	on_game_start();
	while (!quit) {
		on_game_loop();
	}
}

void Game::game_end() {
	quit = true;
}

void Game::game_restart() {
	restart = true;
}

Entity* Game::instance_add(std::shared_ptr<Entity> inst) {
	entities.emplace_back(inst);
	inst->game = this;
	inst->input = input;
	inst->graphics = graphics;
	return inst.get();
}

void Game::instance_remove(Entity* inst) {
	entities.erase(std::find_if(entities.begin(), entities.end(), [&inst](auto i) {return i.get() == inst;} ));
}