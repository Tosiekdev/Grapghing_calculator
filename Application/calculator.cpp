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
                _tools.add_function();
            }
        }
        if (e_.type == sf::Event::MouseWheelScrolled) {
            _tools.scroll_scale(e_.mouseWheelScroll.delta);
        }
        if (e_.type == sf::Event::MouseButtonPressed) {
            _bufMousePos = sf::Mouse::getPosition();
        }
        if (e_.type == sf::Event::MouseButtonReleased) {
            _bufMousePos = sf::Vector2i(-1, -1);
        }
    }
}

void Calculator::do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    ImGui::SFML::Update(window, deltaClock.restart());

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto mousePos = sf::Mouse::getPosition();
        _tools.shift_graph(window, _bufMousePos, mousePos);
        _bufMousePos = mousePos;
    }

    title(window, scene);
    returning_button(window, deltaClock, scene);
    _tools.show_scale(window);
    _tools.show_numbers(window);
    _tools.show(window, scene);
}

void Calculator::display(sf::RenderWindow &window){
    window.clear(sf::Color::White);

    _tools.show_canvas(window);

    ImGui::SFML::Render(window);

    window.display();
}

