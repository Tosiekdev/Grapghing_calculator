//
// Created by tosiek on 11.06.22.
//

#include "window.h"

void Window::returning_button(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    //Getting window's size for scaling
    auto size = window.getSize();
    auto x = static_cast<float>(size.x);
    auto y = static_cast<float>(size.y);

    ImVec2 buttonSize = ImVec2(x/12.f,y/18.f);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(x/10.f,y/10.f));

    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
    ImGui::Begin("Returning Button", nullptr, flags);

    //Color theme
    ImGui::StyleColorsLight();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    if ( ImGui::Button("Return", buttonSize) ) {
        scene = MENU;
    }
    ImGui::PopFont();
    ImGui::End();
    ImGui::PopStyleVar();
}

void Window::title(sf::RenderWindow &window, Scene &scene) {
    //Getting window's size for scaling
    auto size = window.getSize();
    auto x = static_cast<float>(size.x);
    auto y = static_cast<float>(size.y);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(x,y/13.5f));

    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    //Color theme
    ImGui::StyleColorsClassic();

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
    ImGui::Begin("Title bar", nullptr, flags);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    text_centered("AZ Graphing Calculator");
    ImGui::PopFont();
    ImGui::End();
    ImGui::PopStyleVar();
}

void Window::background(sf::RenderWindow &window, Scene &scene) {
    //Getting window's size for scaling
    auto size = window.getSize();
    auto x = static_cast<float>(size.x);
    auto y = static_cast<float>(size.y);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(0,y/13.5f));
    ImGui::SetNextWindowSize(ImVec2(x,y-y/13.5f));

    //Color theme
    ImGui::StyleColorsLight();

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
    ImGui::Begin("Background", nullptr, flags);
    ImGui::End();
}
