#include "entities.h"

Player::Player() {
	initialize();
	name = "Player";
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

	game->camera.setCenter(sf::Vector2f(pos.x, pos.y)); //will make this smooth again soon
}

void Player::on_begin_draw() {

}

void Player::on_draw() {

}

void Player::on_destroy() {
	std::cout << "Player died";
}
