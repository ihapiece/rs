//sfml helper class
#pragma once
#include <map>
#include "vec.h"
#include <SFML/Graphics.hpp>

struct sfmlutil {
  sf::RenderWindow window;
  sf::ContextSettings contextsettings;
  std::vector<sf::RenderTexture*> layers;
  bool fullscreen;
  std::map<sf::Keyboard::Key, bool> last;
  std::map<sf::Keyboard::Key, bool> pressed;
  std::map<sf::Mouse::Button, bool> mlast;
  std::map<sf::Mouse::Button, bool> mpressed;
  sf::Font font_regular;
  Vec mouse;
  Vec mouse_prev;

  sfmlutil();

  void handle_events();
  void render();
  bool is_key_held(sf::Keyboard::Key key);
  bool is_key_pressed(sf::Keyboard::Key key);
  bool is_key_released(sf::Keyboard::Key key);
  bool is_mouse_held(sf::Mouse::Button button);
  bool is_mouse_pressed(sf::Mouse::Button button);
  bool is_mouse_released(sf::Mouse::Button button);
  void to_last();
  void add_layer(sf::RenderTexture* rt); //makes util take care of texture
  void destroy_layer(sf::RenderTexture* t);
};

sf::Vector2f to_sfvec2f(Vec v);
sf::Vector2i to_vec(Vec v);
