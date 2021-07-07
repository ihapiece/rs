#pragma once
#include <map>
#include "vec.h"
#include "graphics.h"
#include <SDL2/SDL.h>

class Input {
public:
	Vec mouse;
	Vec mouseprev;
	bool* quit;
	Graphics* graphics;

	Input(bool* quit_);
	~Input();
	bool keyboard_check(SDL_Keycode k);
	bool keyboard_check_pressed(SDL_Keycode k);
	bool keyboard_check_released(SDL_Keycode k);
	void to_last();
	void update();

private:
	std::map<SDL_Keycode, bool> keys;
	std::map<SDL_Keycode, bool> keys_last;

	void clear();
	void clear_last();
};