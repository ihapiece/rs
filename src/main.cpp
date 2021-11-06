#include "menu.h" //includes game
#include "entities.h"

int main(int argc, char *argv[]) {
	sfmlutil sfml; // give everything a pointer to this
	Game game(&sfml);
	Menu menu(&sfml);
	menu.game = &game;

	float dt;
	game.on_game_start();
	while (sfml.window.isOpen()) {
		sfml.to_last();
		sfml.handle_events();
		sfml.window.clear(sf::Color(0x20,0x20,0x20,0xFF));
		menu.update();
		if (!menu.open) {game.on_game_loop();}
		game.on_game_draw();
		menu.draw();
		sfml.render();
	}

	return 0;
}
