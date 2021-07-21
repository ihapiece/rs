#include "game.h"

Game::Game() {
	input = new Input(&quit);
	graphics = new Graphics;
	input->graphics = graphics;
	quit = false;
	restart = false;

	std::cout << "trying to use aabb\n";
	std::cout << aabb(Vec(1, 1), Vec(10, 10), Vec(5, 5), Vec(20, 20)) << "\n";

	subspace = new Subspace(Vec(400, 320), Vec(100, 100), graphics);
	subspace->add(Vec(100, 340));
}

Game::~Game() {
	delete input;
	delete graphics;
	delete subspace; // temporary
}

void Game::on_game_start() {
	for (auto i : entities) {i->on_game_start();}
}

void Game::on_game_loop() {
	int ticks = SDL_GetTicks();

	input->update();

	if (input->keyboard_check_pressed(SDLK_F4)) {
		graphics->window_toggle_fullscreen();
	}

	for (auto i : entities) {i->t_begin_step();}
	for (auto i : entities) {i->t_step();}
	for (auto i : entities) {i->t_end_step();}

	graphics->draw_set_color(0x00, 0x00, 0x00, 0xFF);
	graphics->draw_clear();
	SDL_SetRenderTarget(graphics->renderer, subspace->subspace_texture);
	graphics->draw_clear();
  SDL_SetRenderTarget(graphics->renderer, NULL);

	for (auto i : entities) {i->t_begin_draw();}
	for (auto i : entities) {i->t_draw();}
	for (auto i : entities) {i->t_end_draw();}
	subspace->draw();

	graphics->draw_flip();

	dt = SDL_GetTicks() - ticks;

	if (dt < 13) {SDL_Delay((1000/60) - dt);}
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
