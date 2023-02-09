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

    for (const auto& x: prepare_graphs(window)) {
        window.draw(x);
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

void Canvas::show_numbers(sf::RenderWindow &window) const {
    float x = static_cast<float>(window.getSize().x);
    float y = static_cast<float>(window.getSize().y);

    // width of the coordinate system
    float graphWidth = x - x / 3.f;

    float step = (graphWidth - 11.f) / 12.f;

    // vertical numbers
    vertical_numbers(x, graphWidth, step, y);

    // horizontal numbers
    horizontal_numbers(x, step, y);
}

void Canvas::vertical_numbers(float x, float graphWidth, float step, float y) const {
    for (int i = 0; i < 11; ++i) {
        auto j = static_cast<float>(i);

        ImGui::SetNextWindowSize(ImVec2(0,0));
        ImGui::SetNextWindowPos(ImVec2(x/3.f+graphWidth/2.f,y/13.5f+j*step));

        int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;

        std::string title = "Vertical number" + std::to_string(i);
        float number = _startEndVertical.second/_scale - j/_scale;
        std::string convertedNumber = std::to_string(number);
        int afterComa = _scale > 1 ? 4 : 3;
        convertedNumber = convertedNumber.substr(0, convertedNumber.find('.')+afterComa);

        ImGui::Begin(title.c_str(), nullptr, flags);
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
        ImGui::Text("%s", convertedNumber.c_str());
        ImGui::PopFont();
        ImGui::End();
    }
}

void Canvas::horizontal_numbers(float x, float step, float y) const {
    for (int i = 0; i < 12; ++i) {
        auto j = static_cast<float>(i);

        ImGui::SetNextWindowSize(ImVec2(0,0));
        ImGui::SetNextWindowPos(ImVec2(x/3.f+j*step,y/27.f+y/2.f));

        int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;

        std::string title = "Horizontal number" + std::to_string(i);
        float number = _startEndHorizontal.first/_scale + j/_scale;
        std::string convertedNumber = std::to_string(number);
        int afterComa = _scale > 1 ? 4 : 3;
        convertedNumber = convertedNumber.substr(0, convertedNumber.find('.')+afterComa);

        ImGui::Begin(title.c_str(), nullptr, flags);
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
        ImGui::Text("%s", convertedNumber.c_str());
        ImGui::PopFont();
        ImGui::End();
    }
}

void Canvas::scroll_scale(float delta) {
    _scalingStep = _scale < 1.f ? 0.01f : 0.1f;
    if (delta > 0) {
        _scale += _scalingStep;
    } else {
        _scale -= _scalingStep;
    }
}

std::vector<std::array<std::pair<float, float>, 1000>> Canvas::evaluate_functions() {
    std::vector<std::array<std::pair<float, float>, 1000>> functions;
    for (std::string &func : _allFunctions) {
        az::Function function;
        function.start(func);
        std::array<std::pair<float, float>, 1000> array;
        for (int i = 0; i < 1000; ++i) {
            auto j = static_cast<float>(i);
            float x = _startEndHorizontal.first / _scale + 12.f / 1000.f * j;
            float y;
            try {
                y = static_cast<float>(function.calc_value(x));
            } catch (az::OutOfDomain &e) {
                y = std::nanf("");
            }
            std::pair<float, float> point = std::make_pair(x, y);
            array[i] = point;
        }
        functions.push_back(array);
    }
    return functions;
}

std::vector<sf::VertexArray> Canvas::prepare_graphs(sf::RenderWindow &window) {
    std::vector<sf::VertexArray> returns;

    auto width = static_cast<float>(window.getSize().x);
    auto height = static_cast<float>(window.getSize().y);

    // calculating graph width
    width = width - width / 3.f;
    float step = (width - 11.f) / 12.f;

    // scaling factor
    float a = width / 12.f * _scale;

    // shifting coefficient
    float b = width / 2.f;

    // vertical shift
    float z = _horizontalLines[4].getPosition().y;

    auto functionsValues = evaluate_functions();

    for (const auto &i:functionsValues) {
        sf::VertexArray plot(sf::TriangleStrip);
        for (const auto &point:i) {
            if (!isnanf(point.second)) {
                //get points
                float x = point.first;
                float y = point.second;

                x -= _startEndHorizontal.first;

                // scale values
                x *= a;
                y *= -a;

                // shift graph
                x += b;
                y += z;

                sf::Vertex top = sf::Vertex(sf::Vector2f(x,y+1),sf::Color::Blue);
                sf::Vertex bottom = sf::Vertex(sf::Vector2f(x,y-1),sf::Color::Blue);
                plot.append(top);
                plot.append(bottom);
            }
        }

        returns.push_back(plot);
    }

    return returns;
}
