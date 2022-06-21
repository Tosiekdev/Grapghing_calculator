//
// Created by tosiek on 11.06.22.
//

#include "app.h"

App::App(){
    current_ = MENU;
    window_.create(sf::VideoMode::getFullscreenModes()[0], "az-math", sf::Style::Fullscreen);
    window_.setMouseCursorGrabbed(false);
}

void App::start(){
    while(window_.isOpen()){
        switch (current_){
            case MENU:
                menu_.handle_events(window_, current_);
                menu_.do_stuff(window_);
                menu_.display(window_);
                break;
            case CALCULATOR:
                calculator_.handle_events(window_,current_);
                calculator_.do_stuff(window_);
                calculator_.display(window_);
                break;
            case INSTRUCTION:
                manual_.handle_events(window_,current_);
                manual_.do_stuff(window_);
                manual_.display(window_);
                break;
        }
    }
}
