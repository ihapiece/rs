#include "menu.h"

Menu::Menu(sfmlutil* s_) : sfml(s_) {
  submenu = 0;
  selection = 0; //these should probably be enums
  mainmenu = {"Let's go", "Achievements", "Options", "Quit"};
}

void Menu::update() {
  
}

void Menu::draw() {

}
