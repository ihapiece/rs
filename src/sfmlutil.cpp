#include "sfmlutil.h"
#include <iostream>

sfmlutil::sfmlutil() {
  contextsettings.antialiasingLevel = 4;
  window.create(sf::VideoMode(400, 200), "RS", sf::Style::Default, contextsettings);
  window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
  font_regular.loadFromFile("assets/texgyreheros-regular.otf");
}

void sfmlutil::handle_events() {
  sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        pressed[event.key.code] = true;
        break;

      case sf::Event::KeyReleased:
        pressed[event.key.code] = false;
        break;

      case sf::Event::Resized:
        for (auto i : layers) {
          i->create(window.getSize().x, window.getSize().y, contextsettings);
        }
        break;

      default:
        break;
    }
  }
}

void sfmlutil::render() {
  window.display();
}

bool sfmlutil::is_key_held(sf::Keyboard::Key key) {
  return pressed[key];
}

bool sfmlutil::is_key_pressed(sf::Keyboard::Key key) {
  return pressed[key] && !last[key];
}

bool sfmlutil::is_key_released(sf::Keyboard::Key key) {
  return !pressed[key] && last[key];
}

void sfmlutil::to_last() {
  for (auto i : pressed) {
    last[i.first] = i.second;
  }
}

void sfmlutil::add_layer(sf::RenderTexture* rt) {
  layers.push_back(rt);
  rt->create(window.getSize().x, window.getSize().y, contextsettings);
}

void sfmlutil::destroy_layer(sf::RenderTexture* t) {
  std::cout << "trying to delete layer at " << t << "\n";
  for (auto i : layers) {
    std::cout << &i << "\n";
  }
}


sf::Vector2f to_sfvec2f(Vec v) {
  return sf::Vector2f(v.x, v.y);
}
