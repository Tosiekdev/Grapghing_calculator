//
// Created by tosiek on 11.06.22.
//

#include "button.h"

Button::Button(){
    texture_.loadFromFile("Textures/button.png");
    sprite_.setTexture(texture_);

    texture_f_.loadFromFile("Textures/focused_button.png");

    caption_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    caption_.setFillColor(sf::Color::Black);
}

void Button::create_button(sf::Vector2f pos, sf::Vector2f scale, const std::string& text){
    sprite_.setPosition(pos);
    sprite_.setScale(scale);

    float center_x=250*scale.x;
    float center_y=75*(scale.y-0.15f);
    sf::Vector2f center=sf::Vector2f(center_x,center_y);

    caption_.setCharacterSize(static_cast<int>(100 * scale.y));
    caption_.setString(text);
    caption_.setPosition(pos + center);
}

bool Button::is_focused(const sf::Vector2i &mouse_pos, sf::Cursor &cursor, sf::RenderWindow& window){
    auto mouse_pos_x=static_cast<float>(mouse_pos.x);
    auto mouse_pos_y=static_cast<float>(mouse_pos.y);

    if(sprite_.getGlobalBounds().contains(mouse_pos_x,mouse_pos_y)){
        sprite_.setTexture(texture_f_);
        cursor.loadFromSystem(sf::Cursor::Hand);
        window.setMouseCursor(cursor);
        return true;
    }

    sprite_.setTexture(texture_);
    return false;
}
