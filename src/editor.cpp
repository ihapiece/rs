#include "game.h"
#include "entities.h"

void Editor::start() {
    open = false;
    mode = nothing;


    hud.setFont(sfml->font_regular);
    hud.setCharacterSize(14);
    hud.setFillColor(sf::Color::White);
}

void Editor::update() {
    if (sfml->is_key_pressed(sf::Keyboard::E)) {
        if (mode == nothing) {mode = blockedit;}
        else if (mode == blockedit) {mode = nothing;}
    }

    if (mode == blockedit) {
        if (sfml->is_mouse_pressed(sf::Mouse::Button::Left)) {
            topleft = sfml->mouse;
        }
        if (sfml->is_mouse_released(sf::Mouse::Button::Left)) {
            Entity* b = game->instance_add(std::make_shared<Block>());
            b->bbr = (sfml->mouse - topleft)/2;
            b->pos = topleft + b->bbr;
            b->btl = b->bbr*-1.0f;
            if (b->btl.x > b->bbr.x) {std::swap(b->btl.x, b->bbr.x);}
            if (b->btl.y > b->bbr.y) {std::swap(b->btl.y, b->bbr.y);}
        }
    }
}

void Editor::draw() {
    sf::Vector2f pos = sfml->window.mapPixelToCoords({0, 0});

    switch(mode) {
        case nothing:
            hud.setString("nothing");
            break;

        case blockedit:
            hud.setString("blockedit");
            break;
    }
    hud.setPosition(pos);
    sfml->window.draw(hud);
}