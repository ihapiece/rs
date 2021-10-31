#include "game.h"

Entity::Entity() {
	initialize();
	name = "Entity";
}

void Entity::initialize() {
	created = false;
	destroyed = false;
	moves = true;
	solid = false;
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
	bshape.setFillColor(sf::Color::White);
	bshape.setOutlineThickness(2.0);
	bshape.setOutlineColor(sf::Color::Black);
}
void Entity::t_draw() {
	on_draw();
	sfml->window.draw(bshape);
}
void Entity::t_end_draw() {on_end_draw();}

void Entity::instance_destroy() {
	destroyed = true;
}

std::string Entity::get_name() {
	return name;
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
			if (game->subspace->ssaabb(pos_+btl, pos_+bbr, i->pos+i->btl, i->pos+i->bbr)) {
				return i.get();
			}
		}
	}
	return NULL;
}

bool Entity::meeting_entity(Vec pos_, Entity* i) {
	if (i != this) {
		if (game->subspace->ssaabb(pos_+btl, pos_+bbr, i->pos+i->btl, i->pos+i->bbr)) {
			return true;
		}
	}
	return false;
}
