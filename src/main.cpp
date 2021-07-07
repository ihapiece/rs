#include "game.h"

class Player : public Entity {
	public:
	Player() {
		initialize();
		name = "Player";
	}

	protected:
	int health;
	virtual void on_create() {
		health = 10;
		pos = Vec(200, 300);
		std::cout << "Player create event\n";
		sprite = "spr_player_strip5"; // TODO make this better
	}
	
	virtual void on_step() {
		bool grounded = false;
		speed.x = (int(input->keyboard_check(SDLK_RIGHT))-int(input->keyboard_check(SDLK_LEFT)))*4;
		speed.y += 1;
		if (input->keyboard_check_pressed(SDLK_UP)) {pos.y--; speed.y = -12;}
		if (input->keyboard_check_released(SDLK_a)) {graphics->camerapos.x--;}
		if (input->keyboard_check_released(SDLK_d)) {graphics->camerapos.x++;}
		if (input->keyboard_check(SDLK_w)) {graphics->scale += 0.02;}
		if (input->keyboard_check(SDLK_s)) {graphics->scale -= 0.02;}
		if (health <= 0) {instance_destroy();}
		if (pos.y >= 480-size.y/2) {pos.y = 480-size.y/2; speed.y = 0; grounded = true;}
		if (speed.x != 0) {xscale = (speed.x/abs(speed.x)); anim_speed = 0.4;} else {subimg = 0; anim_speed = 0;}
		if (!grounded) {anim_speed = 0; subimg = 4;}
	}

	virtual void on_end_step() {
		graphics->camerapos = graphics->camerapos.lerp(pos, 0.1);
	}

	virtual void on_begin_draw() {
		graphics->draw_set_color(0x50, 0x40, 0x30, 0xFF);
		graphics->draw_clear();
	}

	virtual void on_end_draw() {
		graphics->draw_set_color(0xFF, 0xFF, 0xFF, 0xFF);
		graphics->draw_rectangle(pos-size/2, pos+size/2, true);
		//graphics->draw_rectangle(Vec(8, 8), graphics->window_get_size()-Vec(8, 8), true);
		graphics->draw_line(Vec(0, 480), Vec(300, 480));
		graphics->draw_line(pos, pos-Vec(6, 6));
		graphics->draw_line(graphics->camerapos, graphics->camerapos-Vec(6, -6));
	}

	virtual void on_destroy() {
		std::cout << "Player died";
	}
};

int main(int argc, char *argv[]) {
	std::cout << "Entered main\n";
	Game game;
	std::cout << "Game was constructed\n";
	game.graphics->load_sprite("spr_player_strip5", 5);
	game.instance_add(std::make_shared<Player>());
	game.run();
	std::cout << "Game finished running\n";
	return 0;
}