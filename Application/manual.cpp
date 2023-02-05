//
// Created by tosiek on 16.06.22.
//

#include "manual.h"

Manual::Manual(){
    header_.loadFromFile("Textures/header.png");

    title_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    title_.setFillColor(sf::Color::Black);
    title_.setString("AZ-math");
    title_.setCharacterSize(64);
    title_.setPosition(sf::Vector2f(960, 40));

    returning_.create_button(sf::Vector2f(10,10),sf::Vector2f(0.3f,0.4f),"Return");

    caption_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    caption_.setFillColor(sf::Color::Black);
    caption_.setString("This is graphing calculator(probably).\n"
                       "It offers various types of functions such as:\n"
                       "-trigonometric functions,\n"
                       "-cyclometric functions,\n"
                       "-exponetial functions,\n"
                       "-logarithmic functions,\n"
                       "-polynomials.\n"
                       "To make everything looks and works fine remember:\n"
                       "-two arguments symbols (*,^,/) like to work other than BODMAS tells so to be sure use brackets,\n"
                       "-^ means power, * means multiplication (remember to always use it), / means division,\n"
                       "-2x won't work,\n"
                       "-pi in function is treated as 3.1415926563589793,\n"
                       "-e is treated as Euler's number (i don't remember digits),\n"
                       "-this two above doesn't work as an argument.\n"
                       "Have a good time playing with it, don't broke everything.\n"
                       "Bad usage can cause freeze.");
    caption_.setCharacterSize(32);
    caption_.setPosition(sf::Vector2f(960, 580));
}

void Manual::handle_events(sf::RenderWindow &window, Scene &scene) {
    while(window.pollEvent(e_)){
        ImGui::SFML::ProcessEvent(window, e_);
        switch(e_.type){
            case sf::Event::KeyPressed:
                if(e_.key.code == sf::Keyboard::Escape) { scene=MENU; }
                break;
            default:
                ;
        }
    }
}

void Manual::do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    ImGui::SFML::Update(window, deltaClock.restart());

    returningButton(window, deltaClock, scene);
}

void Manual::display(sf::RenderWindow &window){
    window.clear(sf::Color::White);

    window.draw(header_.getSprite());
    window.draw(title_.getText());

    window.draw(caption_.getText());

    ImGui::SFML::Render(window);

    window.display();
}
