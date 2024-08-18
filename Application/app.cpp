//
// Created by tosiek on 11.06.22.
//

#include "app.h"

#include <iostream>

App::App() {
    current_ = MENU;
    window_.create(sf::VideoMode::getFullscreenModes()[0], "az-math", sf::Style::Fullscreen);
    window_.setFramerateLimit(60);
    window_.setMouseCursorGrabbed(false);
}

void App::start() {
    sf::Clock deltaClock;
    if (!ImGui::SFML::Init(window_)) {
        std::cerr << "Failed to initialize ImGui Application" << std::endl;
        std::abort();
    }
    const ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(fontPath, 32.f);
    io.Fonts->AddFontFromFileTTF(fontPath, 64.f);
    io.Fonts->AddFontFromFileTTF(fontPath, 24.f);
    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "Failed to update font" << std::endl;
        std::abort();
    }
    while (window_.isOpen()) {
        switch (current_) {
            case MENU:
                menu_.handle_events(window_, current_);
                menu_.do_stuff(window_, deltaClock, current_);
                menu_.display(window_);
                break;
            case CALCULATOR:
                calculator_.handle_events(window_, current_);
                calculator_.do_stuff(window_, deltaClock, current_);
                calculator_.display(window_);
                break;
            case INSTRUCTION:
                manual_.handle_events(window_, current_);
                manual_.do_stuff(window_, deltaClock, current_);
                manual_.display(window_);
                break;
        }
    }
    ImGui::SFML::Shutdown();
}
