#pragma once
#include "vec.h"
#include <map>
#include <string>
#include <cstring>
#include <malloc.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Sprite {
	SDL_Texture* texture;
	uint8_t subimgcount;
	int width;
	int height;
};

class Graphics {
public:
	SDL_Color draw_color;
	std::map<std::string, Sprite*> sprites;

	float scale;
	Vec camerapos;
	bool to_camera;

	Graphics();
	~Graphics();

	void window_refresh();
	void window_toggle_fullscreen();
	bool window_get_fullscreen();
	Vec window_get_size();

	void draw_set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void draw_set_color(SDL_Color& c);
	void draw_clear();
	void draw_flip();
	void draw_line(Vec p1, Vec p2);
	void draw_rectangle(Vec p1, Vec p2, bool outline);
	void draw_roundrect(Vec p1, Vec p2, float radius, bool outline);
	void draw_triangle(Vec p1, Vec p2, Vec p3, bool outline);

	void load_sprite(const std::string& filename, int subimgcount);
	void draw_sprite(const std::string& sprname, int subimg, Vec pos);
	void draw_sprite_ex(const std::string& sprname, int subimg, Vec pos, float angle, float xscale, float yscale);
	float get_sprite_width(const std::string& sprname);
	float get_sprite_height(const std::string& sprname);
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_DisplayMode display;

	bool fullscreen;
	Vec windowsize;
	Vec t_windowsize;
};
