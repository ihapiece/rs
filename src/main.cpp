#include "game.h"
#include "entities.h"

// reminder: there's a command that generates the SDL compile command

// todo at the moment
// - switch to SFML, i can't be bothered with SDL's shit anymore
//
// - main/pause menu (same thing to be simple)
// - subspaces
// - move the player and stuff to their own files you animal
// - world and world serialization
// - saving and loading
// - asset unpacking with physfs
// - rotatable subspaces
// - slopes
// - subspace teleportation

int main(int argc, char *argv[]) {
	bool quit = false;
	bool restart = false;
	sf::RenderWindow window;

	Game game(&quit);

	//normally the menu class would handle this, but it doesn't exist yet
	game.instance_add(std::make_shared<Player>());
	auto b = game.instance_add(std::make_shared<Block>());
	b->pos = Vec(200, 480);
	b->btl = Vec(-600, -32);
	b->bbr = Vec(600, 32);
	b = game.instance_add(std::make_shared<Block>());
	b->pos = Vec(300, 320);
	b->btl = Vec(-16, -40);
	b->bbr = Vec(16, 40);
	b = game.instance_add(std::make_shared<WavingBlock>());
	b->pos = Vec(200, 480-64);
	b->btl = Vec(-32, -32);
	b->bbr = Vec(32, 32);
	for (int i = 0; i < 100; i++) {
		b = game.instance_add(std::make_shared<Block>());
		b->pos = Vec(0, i*32);
		b->btl = Vec(-16, -16);
		b->bbr = Vec(16, 16);
	}

	float dt;
	game.on_game_start();
	while (!quit) {


		if (input.keyboard_check_pressed(SDLK_F4)) {
			graphics.window_toggle_fullscreen();
		}

		if (input.keyboard_check_pressed(SDLK_r)) {
			restart = true;
		}

		game.on_game_loop();


	}

	return 0;
}
