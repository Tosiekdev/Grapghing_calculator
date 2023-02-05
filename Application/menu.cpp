//
// Created by tosiek on 11.06.22.
//

#include "imgui.h"
#include "imgui-SFML.h"

#include "menu.h"

Menu::Menu(){
    is_focused=false;

    header_.loadFromFile("Textures/header.png");
    header_.setPosition(sf::Vector2f(0, 0));

    title_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    title_.setFillColor(sf::Color::Black);
    title_.setString("AZ-math");
    title_.setCharacterSize(64);
    title_.setPosition(sf::Vector2f(960, 40));
}

void Menu::handle_events(sf::RenderWindow &window, Scene &scene) {
    while(window.pollEvent(e_)){
        ImGui::SFML::ProcessEvent(window, e_);
        switch (e_.type){
            case sf::Event::KeyPressed:
                if(e_.key.code == sf::Keyboard::Escape) { window.close(); }
                break;
            default:
                ;
        }
    }
}

void Menu::do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    ImGui::SFML::Update(window, deltaClock.restart());
    menuOptions(window, deltaClock, scene);

    //ImGui::ShowDemoWindow();
}

void Menu::display(sf::RenderWindow &window){
    window.clear(sf::Color::White);

    window.draw(header_.getSprite());
    window.draw(title_.getText());

    ImGui::SFML::Render(window);

    window.display();
}

void Menu::menuOptions(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    //Getting window's size for scaling
    auto size = window.getSize();
    auto x = static_cast<float>(size.x);
    auto y = static_cast<float>(size.y);

    ImVec2 buttonSize = ImVec2(x/5.f,y/12.f);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(2.f*x/5.f,7.f*y/24.f));
    ImGui::SetNextWindowSize(ImVec2(x/4.f,y/2.4f));

    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
    ImGui::Begin("a", nullptr, flags);

    //Color theme
    ImGui::StyleColorsLight();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    if ( ImGui::Button("Calculator", buttonSize) ) {
        scene = CALCULATOR;
    }
    ImGui::Text("");
    if ( ImGui::Button("Manual", buttonSize) ) {
        scene = INSTRUCTION;
    }
    ImGui::Text("");
    if ( ImGui::Button("Exit", buttonSize) ) {
        window.close();
    }
    ImGui::PopFont();
    ImGui::End();
    ImGui::PopStyleVar();
}
