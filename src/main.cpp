#include "game.h"

// todo at the moment
// - subspaces
// - move the player and stuff to their own files you animal
// - world and world serialization
// - saving and loading
// - asset unpacking with physfs
// - rotatable subspaces
// - slopes
// - subspace teleportation

class Player : public Entity {
	public:
	Player() {
		initialize();
		name = "Player";
	}

	protected:
	Entity* ground;
	unsigned char coyote;
	float gaccel;
	float friction;
	float maxspeed;
	float aaccel;
	float airres;

	virtual void on_create() {
		gaccel = .5;
		friction = 1;
		maxspeed = 4;
		aaccel = .3;
		airres = .6;
		pos = Vec(200, 300);
		btl = Vec(-8, -10);
		bbr = Vec(8, 24);
		std::cout << "Player create event\n";
		sprite = "spr_player_strip5"; // TODO make this better
		anim_speed = 0;
	}

	virtual void on_step() {
		if (coyote > 0) {coyote--;}
		ground = meeting_solid(pos+Vec(0, 1));
		if (ground == NULL) {speed.y += .5;} else {coyote = 6;}
		int move = int(input->keyboard_check(SDLK_d))-int(input->keyboard_check(SDLK_a));
		//std::cout << move << "\n";
		if (input->keyboard_check_pressed(SDLK_w) && coyote > 0) {speed.y = -8; coyote = 0;}

		if (ground != NULL) {
			if (move != 0) {
				if (speed.x*move < maxspeed) {speed.x += move*gaccel;}
			} else {
				speed.x += friction*-sign(speed.x);
				if (speed.x < friction) {speed.x = 0;}
			}
		} else {
			if (move != 0) {
				if (speed.x*move < maxspeed) {speed.x += move*aaccel;}
			} else {
				speed.x += airres*-sign(speed.x);
				if (speed.x < airres) {speed.x = 0;}
			}
		}

		pos += speed;
	}

	virtual void on_end_step() {
		if (ground) {
			if (ground->moves) {
				pos += ground->pos - ground->pos_previous;
			}
		}
		unsigned char n = 0;
		while (Entity* i = meeting_solid(pos)) {
			n++;
			if (n > 5) {break;}
			int u = 0; int d = 0; int l = 0; int r = 0;
			while (meeting_entity(pos+Vec(0, u), i)) {u--;}
			while (meeting_entity(pos+Vec(0, d), i)) {d++;}
			if (d > abs(u)) {d = u;}
			while (meeting_entity(pos+Vec(l, 0), i)) {l--;}
			while (meeting_entity(pos+Vec(r, 0), i)) {r++;}
			if (r > abs(l)) {r = l;}
			if (abs(d) < abs(r)) {speed.y = int(!(speed.y * d < 0)); pos.y += d;} else {speed.x = int(!(speed.x * r < 0)); pos.x += r;}
		}

		graphics->camerapos = graphics->camerapos.lerp(pos, 0.1);
	}

	virtual void on_begin_draw() {
		graphics->draw_set_color(0x50, 0x40, 0x30, 0xFF);
		graphics->draw_clear();
	}

	virtual void on_draw() {
		graphics->draw_sprite_ex(sprite, subimg, pos, angle, xscale, yscale);
		SDL_SetRenderTarget(graphics->renderer, game->subspace->subspace_texture);
		graphics->draw_sprite_ex(sprite, subimg, pos-game->subspace->tl[0], angle, xscale, yscale);
		SDL_SetRenderTarget(graphics->renderer, NULL);
	}

	virtual void on_destroy() {
		std::cout << "Player died";
	}
};

class Block : public Entity {
public:
	Block() {
		initialize();
		name = "Block";
		solid = true;
		moves = false;
	}

	virtual void on_end_draw() {
		graphics->draw_set_color(0xff, 0xff, 0xff, 0x00);
		graphics->draw_rectangle(pos+btl, pos+bbr, false);
		SDL_SetRenderTarget(graphics->renderer, game->subspace->subspace_texture);
		graphics->draw_rectangle(pos+btl-game->subspace->tl[0], pos+bbr-game->subspace->tl[0], false);
		SDL_SetRenderTarget(graphics->renderer, NULL);
	}
};

class WavingBlock : public Entity {
public:
	float t;
	float basey;
	float basex;
	WavingBlock() {
		initialize();
		name = "WavingBlock";
		solid = true;
	}

	virtual void on_create() {
		t = 0;
		basey = pos.y;
		basex = pos.x;
	}

	virtual void on_step() {
		t++;
		pos.y = basey+sin(t/60)*100;
		pos.x = basex+cos(t/60)*100;
	}

	virtual void on_end_draw() {
		graphics->draw_set_color(0xff, 0xff, 0xff, 0x00);
		graphics->draw_rectangle(pos+btl, pos+bbr, false);
		SDL_SetRenderTarget(graphics->renderer, game->subspace->subspace_texture);
		graphics->draw_rectangle(pos+btl, pos+bbr, false);
		SDL_SetRenderTarget(graphics->renderer, NULL);
	}
};

int main(int argc, char *argv[]) {
	std::cout << "Entered main\n";
	Game game;
	std::cout << "Game was constructed\n";
	game.graphics->load_sprite("spr_player_strip5", 5);
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
	game.run();
	std::cout << "Game finished running\n";
	return 0;
}
