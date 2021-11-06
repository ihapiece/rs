#include "entities.h"

Player::Player() {
	initialize();
	saveid = 0;
}

void Player::on_create() {
	gaccel = .5;
	friction = 1;
	maxspeed = 3;
	aaccel = .3;
	airres = .6;
	pos = Vec(200, 300);
	btl = Vec(-8, -10);
	bbr = Vec(8, 24);
	coyote = 0;
	bshape.setFillColor(sf::Color::Cyan);
}

void Player::on_step() {

	if (coyote > 0) {coyote--;}
	ground = meeting_solid(pos+Vec(0, 1));
	if (ground == NULL) {speed.y += .5;} else {coyote = 6;}
	int move = int(sfml->is_key_held(sf::Keyboard::D))-int(sfml->is_key_held(sf::Keyboard::A));
	if (sfml->is_key_pressed(sf::Keyboard::W) && coyote > 0) {speed.y = -8; coyote = 0;}
	if (sfml->is_key_held(sf::Keyboard::RBracket)) {game->zoom+=0.02;}
	if (sfml->is_key_held(sf::Keyboard::LBracket)) {game->zoom-=0.02;}
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

void Player::on_end_step() {
	if (ground) {
		if (ground->moves) {
			pos += ground->pos - ground->pos_previous;
		}
	}
	
	resolve_collisions();

	game->camera.setCenter(to_sfvec2f(Vec(game->camera.getCenter().x, game->camera.getCenter().y).lerp(pos, 0.05))); //will make this smooth again soon
}

void Player::on_begin_draw() {

}

void Player::on_draw() {

}

void Player::on_destroy() {
	std::cout << "Player died";
}
