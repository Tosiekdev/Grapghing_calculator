//
// Created by tosiek on 11.06.22.
//

#include "menu.h"

Menu::Menu(){
    is_focused=false;

    background_.loadFromFile("Textures/back.jpg");
    background_.setPosition(sf::Vector2f(0, 0));

    header_.loadFromFile("Textures/header.png");
    header_.setPosition(sf::Vector2f(0, 0));

    title_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    title_.setFillColor(sf::Color::Black);
    title_.setString("AZ-math");
    title_.setCharacterSize(64);
    title_.setPosition(sf::Vector2f(960, 40));

    calculator_.create_button(sf::Vector2f(810, 280), sf::Vector2f(0.6f, 0.5f), "Calculator");
    manual_.create_button(sf::Vector2f(810, 485), sf::Vector2f(0.6f, 0.5f), "Manual");
    exit_.create_button(sf::Vector2f(810, 680), sf::Vector2f(0.6f, 0.5f), "Exit");
}

void Menu::handle_events(sf::RenderWindow &window, Scene& scene){
    while(window.pollEvent(e_)){
        switch (e_.type){
            case sf::Event::KeyPressed:
                if(e_.key.code == sf::Keyboard::Escape) { window.close(); }
                break;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            auto mouse=sf::Mouse::getPosition(window);

            if(calculator_.is_focused(mouse,cursor_,window)){ scene=CALCULATOR; }
            if(manual_.is_focused(mouse,cursor_,window)) { scene=INSTRUCTION; }
            if(exit_.is_focused(mouse,cursor_,window)){ window.close(); }
        }
    }
}

void Menu::do_stuff(sf::RenderWindow &window){
    is_focused=calculator_.is_focused(sf::Mouse::getPosition(window),cursor_,window);
    if(!is_focused){
        is_focused=manual_.is_focused(sf::Mouse::getPosition(window),cursor_,window);
    }
    if(!is_focused){
        is_focused=exit_.is_focused(sf::Mouse::getPosition(window),cursor_,window);
    }

    if(!is_focused){
        cursor_.loadFromSystem(sf::Cursor::Arrow);
        window.setMouseCursor(cursor_);
    }
}

void Menu::display(sf::RenderWindow &window){
    window.clear(sf::Color::White);

    window.draw(background_.getSprite());
    window.draw(header_.getSprite());
    window.draw(title_.getText());

    window.draw(calculator_.getSprite());
    window.draw(calculator_.getCaption());

    window.draw(manual_.getSprite());
    window.draw(manual_.getCaption());

    window.draw(exit_.getSprite());
    window.draw(exit_.getCaption());

    window.display();
}
