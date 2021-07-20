#include "input.h"

Input::Input(bool* quit_) : quit(quit_) {}
Input::~Input() {}

void Input::to_last() {
	for (auto i : keys) {
		keys_last[i.first] = i.second;
		//std::cout << i.first << ":" << i.second << "\n";
	}
	mouseprev = mouse;
}

bool Input::keyboard_check(SDL_Keycode k) {
	return keys[k];
}

bool Input::keyboard_check_pressed(SDL_Keycode k) {
	return keys[k] && !keys_last[k];
}

bool Input::keyboard_check_released(SDL_Keycode k) {
	return !keys[k] && keys_last[k];
}

void Input::update() {
	to_last();
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				*quit = true;
				break;

			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						graphics->window_refresh();
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				mouse.x = event.motion.x;
				mouse.y = event.motion.y;
				break;

			case SDL_KEYUP:
				if (!event.key.repeat) {
					keys[event.key.keysym.sym] = false;
				}
				break;
			case SDL_KEYDOWN:
				if (!event.key.repeat) {
					keys[event.key.keysym.sym] = true;
				}
				break;

			default:
				break;
		}
	}
}
