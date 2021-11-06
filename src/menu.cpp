#include "menu.h"

Menu::Menu(sfmlutil* s_) : sfml(s_) {
  submenu = 0;
  selection = 3; //these should probably be enums
  open = false;
  mainmenu = {"  quit", "  options", "  save level", "  load level"};

  slope = 5;
  dark.setFillColor(sf::Color::Black);

  menubg.setPrimitiveType(sf::TriangleStrip);
  menubg.resize(5);
  menubg[0].color = sf::Color::Black;
  menubg[4].color = menubg[3].color = menubg[2].color = menubg[1].color = menubg[0].color;

  sf::BlendMode diff(sf::BlendMode::Factor::One, sf::BlendMode::Factor::One, sf::BlendMode::Equation::Subtract);
  whitedifference.blendMode = diff;
  bluemultiply.blendMode = sf::BlendMultiply;
  cursor.setPointCount(4);
  text.setFont(sfml->font_regular);
  charsize = 64;
  text.setCharacterSize(charsize);

}

void Menu::update() {
  if (!open) {
    if (sfml->is_key_pressed(sf::Keyboard::Escape)) {
      open = true;
      clock_opened.restart();
    }
  } else {
    if (sfml->is_key_pressed(sf::Keyboard::Escape)) {open = false;}
    if (sfml->is_key_pressed(sf::Keyboard::W)) {selection++;}
    if (sfml->is_key_pressed(sf::Keyboard::S)) {selection--;}
    if (sfml->is_key_pressed(sf::Keyboard::Enter)) {
      switch (selection) {
        case 0:
          game->game_end();
          break;

        case 3:
          Room room("assets/testarea.room");
          game->deploy_room(room);
          break;
      }
    }
    selection = selection % mainmenu.size();
  }

  entrance += (int(open)*2-1)*0.05;
  entrance = std::clamp(entrance, 0.f, 1.f);
}

void Menu::draw() {
  if (entrance > 0) {
    sf::Vector2f pos = sfml->window.mapPixelToCoords({0, 0});
    sf::Vector2f size(sfml->window.getView().getSize().x, sfml->window.getView().getSize().y);
    size.x++; size.y++;

    dark.setFillColor(sf::Color(0, 0, 0, int(entrance*100.0)));
    dark.setSize(size);
    dark.setPosition(pos);
    sfml->window.draw(dark);

    text.setScale(size.y/(8*charsize), size.y/(8*charsize));

    width = int(size.x)/2;
    width *= easeInOutQuad(entrance);

    menubg[0].position = pos + sf::Vector2f(size.x-width, size.y);
    menubg[1].position = pos + sf::Vector2f(size.x-width+(size.y/slope), 0);
    menubg[2].position = pos + sf::Vector2f(size.x*2, 0);
    menubg[3].position = pos + sf::Vector2f(size.x*2, size.y);
    menubg[4].position = menubg[0].position;
    sfml->window.draw(menubg);

    text.setOrigin(0, 0);
    int i = 2;
    for (auto s : mainmenu) {
      text.setString(s);
      float y = size.y-(i*text.getScale().y*charsize*1.2);
      text.setPosition(pos + sf::Vector2f(size.x-width+((size.y-y)/slope), y));
      i++;
      text.setFillColor(sf::Color::White);
      sfml->window.draw(text);
    }

    cursory = lerp(cursory, size.y-(1.2*selection+2.2)*text.getScale().y*charsize, 0.2);
    float cursoryb = cursory+text.getScale().y*charsize*1.1;
    cursor.setPoint(0, pos + sf::Vector2f(size.x-width+10+((size.y-cursoryb)/slope), cursoryb));
    cursor.setPoint(1, pos + sf::Vector2f(size.x-width+10+((size.y-cursory)/slope), cursory));
    cursor.setPoint(2, pos + sf::Vector2f(size.x*2, cursory));
    cursor.setPoint(3, pos + sf::Vector2f(size.x*2, cursoryb));
    sf::FloatRect lb = cursor.getLocalBounds();
    cursor.setTextureRect(sf::IntRect(-pos.x + lb.left, -pos.y + lb.top, lb.width, lb.height));

    cursor.setFillColor(sf::Color::White);
    sfml->window.draw(cursor, whitedifference);
    cursor.setFillColor(sf::Color(0x66, 0x99, 0xff));
    sfml->window.draw(cursor, bluemultiply);
  }
}
