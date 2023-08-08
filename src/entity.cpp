#include "game.h"

Entity::Entity() {
	initialize();
	saveid = -1; //entity not to be saved
}

void Entity::initialize() {
	created = false;
	destroyed = false;
	moves = true;
	solid = false;
	bshape.setFillColor(sf::Color::Transparent);
	bshape.setOutlineThickness(1);
	bshape.setOutlineColor(sf::Color::Black);
}

void Entity::t_begin_step() {
	if (!created) {on_create(); pos_start = pos; created = true;}
	if (destroyed) {
		on_destroy();
		game->instance_remove(this);
	}

	pos_previous = pos;
	on_begin_step();
}

void Entity::t_step() {
	on_step();
}

void Entity::t_end_step() {on_end_step();}
void Entity::t_begin_draw() {
	on_begin_draw();
	bshape.setOrigin(sf::Vector2f(-btl.x, -btl.y));
	bshape.setSize(sf::Vector2f(bbr.x-btl.x, bbr.y-btl.y));
	bshape.setPosition(sf::Vector2f(int(pos.x), int(pos.y)));
}
void Entity::t_draw() {
	on_draw();
	sfml->window.draw(bshape);
	game->draw_to_ss(bshape, &bshape);
}
void Entity::t_end_draw() {on_end_draw();}

void Entity::instance_destroy() {
	destroyed = true;
}

void Entity::on_create() {}
void Entity::on_game_start() {}
void Entity::on_begin_step() {}
void Entity::on_step() {}
void Entity::on_end_step() {}
void Entity::on_begin_draw() {}
void Entity::on_draw() {}
void Entity::on_end_draw() {}
void Entity::on_destroy() {}
void Entity::on_game_end() {}

Entity* Entity::meeting_solid(Vec pos_) {
	for (auto i : game->entities) {
		if (i.get() != this && i->solid) {
			if (game->ssaabb(pos_+btl, pos_+bbr, i->pos+i->btl, i->pos+i->bbr)) {
				return i.get();
			}
		}
	}
	return NULL;
}

bool Entity::meeting_entity(Vec pos_, Entity* i) {
	if (i != this) {
		if (game->ssaabb(pos_+btl, pos_+bbr, i->pos+i->btl, i->pos+i->bbr)) {
			return true;
		}
	}
	return false;
}

bool Entity::resolve_collisions() {
	unsigned char n = 0;
	while (Entity* i = meeting_solid(pos)) {
		n++;
		if (n > 5) {return false; break;}
		int u = 0; int d = 0; int l = 0; int r = 0;
		while (meeting_entity(pos+Vec(0, u), i)) {u--;} // i dont think this game's physics are per
		while (meeting_entity(pos+Vec(0, d), i)) {d++;} // pixel, might have to change this to something
		if (d > abs(u)) {d = u;}
		while (meeting_entity(pos+Vec(l, 0), i)) {l--;} // that finds the edge of a block
		while (meeting_entity(pos+Vec(r, 0), i)) {r++;}
		if (r > abs(l)) {r = l;}
		if (abs(d) < abs(r)) {speed.y = int(!(speed.y * d < 0)); pos.y += d;} else {speed.x = int(!(speed.x * r < 0)); pos.x += r;}
	}
	return true;
}
