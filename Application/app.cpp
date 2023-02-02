//
// Created by tosiek on 11.06.22.
//

#include "app.h"
#include "imgui-SFML.h"

App::App(){
    current_ = MENU;
    window_.create(sf::VideoMode::getFullscreenModes()[0], "az-math", sf::Style::Fullscreen);
    window_.setMouseCursorGrabbed(false);
}

void App::start(){
    sf::Clock deltaClock;
    ImGui::SFML::Init(window_);
    while(window_.isOpen()){
        switch (current_){
            case MENU:
                menu_.handle_events(window_, current_, deltaClock);
                menu_.do_stuff(window_, sf::Clock());
                menu_.display(window_);
                break;
            case CALCULATOR:
                calculator_.handle_events(window_, current_, deltaClock);
                calculator_.do_stuff(window_, deltaClock);
                calculator_.display(window_);
                break;
            case INSTRUCTION:
                manual_.handle_events(window_, current_, deltaClock);
                manual_.do_stuff(window_, deltaClock);
                manual_.display(window_);
                break;
        }
    }
    ImGui::SFML::Shutdown();
}
