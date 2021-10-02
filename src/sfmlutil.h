//sfml helper class
#pragma once
#include <map>
#include <SFML/Graphics.hpp>

struct sfmlutil {
  sf::RenderWindow window;
  sf::ContextSettings contextsettings;
  bool fullscreen;
  sf::Clock frameclock;
  float delta;
  std::map<sf::Keyboard::Key, bool> last;
  std::map<sf::Keyboard::Key, bool> pressed;

  sfmlutil();

  void handle_events();
  void render();
  bool is_key_held(sf::Keyboard::Key key);
  bool is_key_pressed(sf::Keyboard::Key key);
  bool is_key_released(sf::Keyboard::Key key);
  void to_last();
};
