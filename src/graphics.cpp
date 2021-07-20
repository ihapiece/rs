#include "graphics.h"
#include <iostream>

Graphics::Graphics() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GetDesktopDisplayMode(0, &display);

	windowsize = {640, 360};
	window = SDL_CreateWindow("GMist", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowsize.x, windowsize.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	to_camera = true;
	scale = 1;
}

Graphics::~Graphics() {
	for (auto i : sprites) {
		delete i.second;
	}
	SDL_Quit();
}

void Graphics::window_refresh() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	windowsize = {w, h};
	scale = round(windowsize.y/360.0);
	std::cout << windowsize.y/360.0 << "\n";
}

void Graphics::window_toggle_fullscreen() {
	auto flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    bool fullscreen = SDL_GetWindowFlags(window) & flag;
    SDL_SetWindowFullscreen(window, fullscreen ? 0 : flag);
    SDL_ShowCursor(fullscreen);
}

bool Graphics::window_get_fullscreen() {
	return fullscreen;
}

Vec Graphics::window_get_size() {
	return windowsize;
}

void Graphics::draw_set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Graphics::draw_set_color(SDL_Color& c) {
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void Graphics::draw_clear() {
	SDL_RenderClear(renderer);
}

void Graphics::draw_flip() {
	SDL_RenderPresent(renderer);
}

void Graphics::draw_line(Vec p1, Vec p2) {
	p1 *= scale; p2 *= scale;
	p1 -= camerapos*scale - windowsize/2;
	p2 -= camerapos*scale - windowsize/2;
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void Graphics::draw_triangle(Vec p1, Vec p2, Vec p3, bool outline) {

}

void Graphics::draw_rectangle(Vec p1, Vec p2, bool outline) {
	p1 *= scale; p2 *= scale;
	p1 -= camerapos*scale - windowsize/2;
	p2 -= camerapos*scale - windowsize/2;
	SDL_Rect r = {p1.x, p1.y, p2.x-p1.x, p2.y-p1.y};
	if (outline) {
		SDL_RenderDrawRect(renderer, &r);
	} else {
		SDL_RenderDrawRect(renderer, &r);
	}
}

void Graphics::load_sprite(const std::string& filename, int subimgcount) {
	sprites[filename] = new Sprite();
	Sprite* spr = sprites[filename];
	std::cout << "loading sprite " << filename << "...\n";
	SDL_Surface* surf = IMG_Load((filename+".png").c_str());
	spr->texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	spr->subimgcount = subimgcount;
	SDL_QueryTexture(spr->texture, NULL, NULL,  &spr->width, &spr->height);
	spr->width /= subimgcount;
}

void Graphics::draw_sprite(const std::string& sprname, int subimg, Vec pos) {
	draw_sprite_ex(sprname, subimg, pos, 0, 1, 1);
}

void Graphics::draw_sprite_ex(const std::string& sprname, int subimg, Vec pos, float angle, float xscale, float yscale) {
	Sprite* spr = sprites[sprname];
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (xscale < 0) {flip = SDL_FLIP_HORIZONTAL;}
	if (yscale < 0) {flip = SDL_FLIP_VERTICAL;}
	xscale = abs(xscale); yscale = abs(yscale);
	Vec p1 = pos-Vec(spr->width*xscale, spr->height*yscale)/2;
	Vec p2 = pos+Vec(spr->width*xscale, spr->height*yscale)/2; //no idea why this is like this
	SDL_Rect src = {(subimg%spr->subimgcount)*spr->width, 0, spr->width, spr->height};
	p1 *= scale; p2 *= scale;
	p1 -= camerapos*scale - windowsize/2;
	p2 -= camerapos*scale - windowsize/2;
	SDL_Rect dest = {p1.x, p1.y, p2.x-p1.x, p2.y-p1.y};
	SDL_RenderCopyEx(renderer, spr->texture, &src, &dest, angle, NULL, flip);
}

float Graphics::get_sprite_width(const std::string& sprname) {
	return sprites[sprname]->width;
}

float Graphics::get_sprite_height(const std::string& sprname) {
	return sprites[sprname]->height;
}
