#include "menu.h" //includes game
#include "entities.h"

int main(int argc, char *argv[]) {
	sfmlutil sfml; // give everything a pointer to this
	Game game(&sfml);
	Menu menu(&sfml);

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
	while (sfml.window.isOpen()) {
		sfml.to_last();
		sfml.delta = sfml.frameclock.restart().asMilliseconds();
		sfml.handle_events();
		sfml.window.clear(sf::Color(40, 30, 10));
		menu.update();
		if (!menu.open) {game.on_game_loop();}
		game.on_game_draw();
		menu.draw();
		sfml.render();
	}

	return 0;
}
