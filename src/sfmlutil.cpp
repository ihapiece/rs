#include "sfmlutil.h"

sfmlutil::sfmlutil() {
  window.create(sf::VideoMode::getDesktopMode(), "RS", sf::Style::Fullscreen);
  window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
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
