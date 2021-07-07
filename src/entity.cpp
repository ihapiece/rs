#include "game.h"

Entity::Entity() {
	initialize();
	name = "Entity";
}

void Entity::initialize() {
	created = false;
	destroyed = false;
	sprite = "none";
	subimg = 0;
	anim_speed = 1;
	subimgf = 0;
	xscale = 1;
	yscale = 1;
	angle = 0;
	use_sprite_size = true;
	color = {0xFF, 0xFF, 0xFF, 0xFF};
}

void Entity::t_begin_step() {
	if (!created) {on_create(); pos_start = pos; created = true;}
	if ((size.x == 0 || size.y == 0) and use_sprite_size) {
		size = {graphics->get_sprite_width(sprite)*xscale, graphics->get_sprite_height(sprite)*yscale};
	}
	if (destroyed) {
		on_destroy();
		game->instance_remove(this);
	}

	pos_previous = pos;
	on_begin_step();
}

void Entity::t_step() {
	on_step();
	pos += speed;
	subimgf += anim_speed;
	if (anim_speed != 0) {subimg = int(subimgf);} else {subimgf = subimg;}
}

void Entity::t_end_step() {on_end_step();}
void Entity::t_begin_draw() {on_begin_draw();}
void Entity::t_draw() {
	on_draw();
	graphics->draw_set_color(color);
	graphics->draw_sprite_ex(sprite, subimg, pos, angle, xscale, yscale);
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
void Entity::on_draw() {/*draw_self()*/}
void Entity::on_end_draw() {}
void Entity::on_destroy() {}
void Entity::on_game_end() {}