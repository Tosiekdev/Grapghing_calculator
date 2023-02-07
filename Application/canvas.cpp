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
    sf::Vector2f verticalLineSizeBolded = sf::Vector2f(3, y - y / 13.5f);
    sf::Vector2f horizontalLineSize = sf::Vector2f(graphWidth, 1);
    sf::Vector2f horizontalLineSizeBolded = sf::Vector2f(graphWidth, 3);

    int a = 0;
    for ( auto& i:_verticalLines ) {
        sf::Vector2f size = a == 5 ? verticalLineSizeBolded : verticalLineSize;
        float posX = a == 5 ? verticalStartX-1 : verticalStartX;
        sf::Color color = a == 5 ? sf::Color::Black : sf::Color(150,150,150);
        i = sf::RectangleShape(size);
        i.setPosition( posX, verticalLineY);
        verticalStartX += step;
        i.setFillColor(color);
        a++;
    }

    int b = 0;
    for (auto& j:_horizontalLines){
        sf::Vector2f size = b == 4 ? horizontalLineSizeBolded : horizontalLineSize;
        float posY = b == 4 ? horizontalStartY-1 : horizontalStartY;
        sf::Color color = b == 4 ? sf::Color::Black : sf::Color(150,150,150);
        j = sf::RectangleShape(size);
        j.setPosition(horizontalLineX, posY);
        horizontalStartY += step;
        j.setFillColor(color);
        b++;
    }
}

std::vector<std::string> &Canvas::all_functions() {
    return _allFunctions;
}

void Canvas::show_scale(sf::RenderWindow &window) {
    //windows size
    float x = static_cast<float>(window.getSize().x);
    float y = static_cast<float>(window.getSize().y);

    ImGui::SetNextWindowSize(ImVec2(x/10.f,y/22.f));
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

void Canvas::show_numbers(sf::RenderWindow &window) {

}
