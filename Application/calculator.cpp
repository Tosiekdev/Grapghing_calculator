//
// Created by tosiek on 14.06.22.
//

#include "calculator.h"

void Calculator::handle_events(sf::RenderWindow &window, Scene &scene) {
    while (window.pollEvent(e_)) {
        ImGui::SFML::ProcessEvent(window, e_);
        if (e_.type == sf::Event::KeyPressed) {
            if (e_.key.code == sf::Keyboard::Escape) { scene = MENU; }
            if (e_.key.code == sf::Keyboard::Enter) {
            }
        }
    }
}

void Calculator::do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    ImGui::SFML::Update(window, deltaClock.restart());

    title(window, scene);
    returning_button(window, deltaClock, scene);
    _tools.show_scale(window);
    _tools.show(window, scene);
    _tools.show_numbers(window);
}

void Calculator::display(sf::RenderWindow &window){
    window.clear(sf::Color::White);

    _tools.show_canvas(window);

    ImGui::SFML::Render(window);

    window.display();
}

