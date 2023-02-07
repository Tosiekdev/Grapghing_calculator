//
// Created by tosiek on 06.02.23.
//

#include "canvas.h"

void Canvas::draw(sf::RenderWindow &window) {
    set_lines(window);

    for (const auto& i:_verticalLines) {
        window.draw(i);
    }

    for (const auto& j:_horizontalLines) {
        window.draw(j);
    }
}

void Canvas::set_lines(sf::RenderWindow& window) {
    float x = static_cast<float>(window.getSize().x);
    float y = static_cast<float>(window.getSize().y);

    // width of the coordinate system
    float graphWidth = x - x / 3.f;

    // y position of lines and x position of starting vertical line
    float verticalLineY = y / 13.5f;
    float step = (graphWidth - 11.f) / 12.f;
    float verticalStartX = x / 3.f + step;

    // x position of lines and y position of starting horizontal line
    float horizontalLineX = x / 3.f;
    float horizontalStartY = y / 13.5f + step;

    // line size
    sf::Vector2f verticalLineSize = sf::Vector2f(1, y - y / 13.5f);
    sf::Vector2f horizontalLineSize = sf::Vector2f(graphWidth, 1);

    for ( auto& i:_verticalLines ) {
        i = sf::RectangleShape( verticalLineSize);
        i.setPosition( verticalStartX, verticalLineY);
        verticalStartX += step;
        i.setFillColor(sf::Color(150,150,150));
    }

    for (auto& j:_horizontalLines){
        j = sf::RectangleShape(horizontalLineSize);
        j.setPosition(horizontalLineX, horizontalStartY);
        horizontalStartY += step;
        j.setFillColor(sf::Color(150,150,150));
    }
}

std::vector<std::string> &Canvas::all_functions() {
    return _allFunctions;
}

void Canvas::show_scale(sf::RenderWindow &window) {
    //windows size
    float x = static_cast<float>(window.getSize().x);
    float y = static_cast<float>(window.getSize().y);

    ImGui::SetNextWindowSize(ImVec2(x/10.f,y/20.f));
    ImGui::SetNextWindowPos(ImVec2(x-x/6.f,y-y/10.f));

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    ImGui::Begin("Scale", nullptr,flags);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
    _scalingStep = _scale < 1.f ? 0.01f:0.1f;
    ImGui::InputScalar("Scale",ImGuiDataType_Float,&_scale,&_scalingStep,nullptr,"%.2f");
    ImGui::PopFont();
    ImGui::End();

    // Limitation for scale
    if (_scale > 10.f) {
        _scale = 10.f;
    }
    if (_scale < 0.01f) {
        _scale = 0.01f;
    }
}
