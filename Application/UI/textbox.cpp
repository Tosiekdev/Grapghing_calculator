//
// Created by tosiek on 15.06.22.
//

#include "textbox.h"

Textbox::Textbox(){
    focused_=false;
    indicator_=0;
    view_text_='|';

    texture_.loadFromFile("Textures/textbox.png");
    sprite_.setTexture(texture_);

    view_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    view_.setCharacterSize(30);
    view_.setFillColor(sf::Color::Black);
    view_.setString(content_);
}

void Textbox::update(char sign){
    if(view_.getText().getGlobalBounds().width<450){
        content_.insert(indicator_, &sign, 1);
        view_text_.insert(indicator_, &sign, 1);
        indicator_++;
        if (focused_) { view_.setString(view_text_); }
        else { view_.setString(content_); }
    }
}

void Textbox::focus(bool state){
    focused_=state;
    if(focused_){ view_.setString(view_text_); }
    else { view_.setString(content_); }
}

void Textbox::erase(){
    if(indicator_>0){
        content_.erase(indicator_-1,1);
        view_text_.erase(indicator_-1,1);
        indicator_--;
    }
    if(focused_){ view_.setString(view_text_); }
    else { view_.setString(content_); }
}

bool Textbox::mouse_above(sf::Vector2i mouse, sf::Cursor &cursor, sf::RenderWindow& window){
    auto mouse_pos_x=static_cast<float>(mouse.x);
    auto mouse_pos_y=static_cast<float>(mouse.y);

    if(sprite_.getGlobalBounds().contains(mouse_pos_x,mouse_pos_y)){
        cursor.loadFromSystem(sf::Cursor::Text);
        window.setMouseCursor(cursor);
        return true;
    }

    return false;
}

void Textbox::create_textbox(sf::Vector2f pos, sf::Vector2f scale){
    sprite_.setScale(scale);
    sprite_.setPosition(pos);
    view_.setPosition(pos+sf::Vector2f(250*scale.x,25*scale.y));
    view_.setCharacterSize(int(30*scale.y));
}

void Textbox::draw(sf::RenderWindow &window){
    window.draw(sprite_);
    window.draw(view_.getText());
}

void Textbox::move_indicator(int direction){
    if(direction>0){
        if(indicator_<content_.size()){
            view_text_.erase(indicator_,1);
            indicator_++;
            view_text_.insert(indicator_,"|");
        }
    }else{
        if(indicator_>0){
            view_text_.erase(indicator_,1);
            indicator_--;
            view_text_.insert(indicator_,"|",1);
        }
    }
    view_.setString(view_text_);
}

void Textbox::clear(){
    content_="";
    view_text_='|';
    indicator_=0;
}
