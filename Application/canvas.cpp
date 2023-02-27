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
    float whole = std::abs(_startEndHorizontal.second - std::floor(_startEndHorizontal.second));
    float verticalStartX = x / 3.f + (1-whole)*step;

    // x position of lines and y position of starting horizontal line
    float horizontalLineX = x / 3.f;
    whole = std::abs(_startEndVertical.second - std::floor(_startEndVertical.second));
    float horizontalStartY = y / 13.5f + (1+whole)*step;

    // line size
    sf::Vector2f verticalLineSize = sf::Vector2f(1, y - y / 13.5f);
    sf::Vector2f verticalLineSizeBolded = sf::Vector2f(3, y - y / 13.5f);
    sf::Vector2f horizontalLineSize = sf::Vector2f(graphWidth, 1);
    sf::Vector2f horizontalLineSizeBolded = sf::Vector2f(graphWidth, 3);

    int a = 0;
    for ( auto& i:_verticalLines ) {
        int zero = static_cast<int>(std::abs(_startEndHorizontal.first))-1;
        sf::Vector2f size = a == zero ? verticalLineSizeBolded : verticalLineSize;
        float posX = a == zero ? verticalStartX-1 : verticalStartX;
        sf::Color color = a == zero ? sf::Color::Black : sf::Color(150,150,150);
        i = sf::RectangleShape(size);
        i.setPosition( posX, verticalLineY);
        verticalStartX += step;
        i.setFillColor(color);
        a++;
    }

    int b = 0;
    for (auto& j:_horizontalLines){
        int zero = static_cast<int>(std::abs(_startEndVertical.second))-1;
        sf::Vector2f size = b == zero ? horizontalLineSizeBolded : horizontalLineSize;
        float posY = b == zero ? horizontalStartY-1 : horizontalStartY;
        sf::Color color = b == zero ? sf::Color::Black : sf::Color(150,150,150);
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
        float shift = std::abs(_startEndHorizontal.first) - 6.f;

        ImGui::SetNextWindowSize(ImVec2(0,0));
        ImGui::SetNextWindowPos(ImVec2(x/3.f+graphWidth/2.f+shift*step,y/13.5f+j*step-18.f));

        int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;

        std::string title = "Vertical number" + std::to_string(i);
        float number = _startEndVertical.second/_scale - j/_scale;
        if (number != 0) {
            std::string convertedNumber = std::to_string(number);
            int afterComa = _scale > 1 ? 4 : 3;
            convertedNumber = convertedNumber.substr(0, convertedNumber.find('.') + afterComa);

            ImGui::Begin(title.c_str(), nullptr, flags);
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
            ImGui::Text("%s", convertedNumber.c_str());
            ImGui::PopFont();
            ImGui::End();
        }
    }
}

void Canvas::horizontal_numbers(float x, float step, float y) const {
    for (int i = 0; i <= _verticalLines.size(); ++i) {
        auto j = static_cast<float>(i);
        float shift = std::abs(_startEndVertical.second)-5.f;

        ImGui::SetNextWindowSize(ImVec2(0,0));
        ImGui::SetNextWindowPos(ImVec2(x/3.f+j*step-24.f,y/13.5f+y/2.f-18.f+shift*step));

        int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;

        std::string title = "Horizontal number" + std::to_string(i);
        float number = _startEndHorizontal.first/_scale + j/_scale;

        std::string convertedNumber;
        if (number == 0) {
            convertedNumber = "0";
        } else {
            convertedNumber = std::to_string(number);
            int afterComa = _scale > 1 ? 4 : 3;
            convertedNumber = convertedNumber.substr(0, convertedNumber.find('.') + afterComa);
        }

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

std::vector<std::array<std::pair<float, float>, Canvas::pointNumber>> Canvas::evaluate_functions() {
    std::vector<std::array<std::pair<float, float>, pointNumber>> functions;
    for (std::string &func : _allFunctions) {
        az::Function function;
        function.start(func);
        std::array<std::pair<float, float>, pointNumber> array;
        for (int i = 0; i < pointNumber; ++i) {
            auto j = static_cast<float>(i);
            float x = _startEndHorizontal.first / _scale + 12.f / static_cast<float>(pointNumber) / _scale * j;
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

    // calculating graph width
    auto width = static_cast<float>(window.getSize().x);
    width = width - width / 3.f;

    // scaling factor
    float a = width / 12.f * _scale;

    // shifting coefficient
    float b = width / 2.f;

    // vertical shift
    float z = _horizontalLines[4].getPosition().y+1;

    auto functionsValues = evaluate_functions();

    int n = 0;
    for (const auto &i:functionsValues) {
        sf::VertexArray plot(sf::TriangleStrip);
        for (auto point : i) {
            if (!isnanf(point.second)) {
                //get points
                float x = point.first;
                float y = point.second;

                x -= _startEndHorizontal.first / _scale;

                // scale values
                x *= a;
                y *= -a;

                // shift graph
                x += b;
                y += z;

                sf::Vertex top, bottom;
                auto color = _functionColors[n % 7];

                float lineThickness = 2.f;

                top = sf::Vertex(sf::Vector2f(x, y + lineThickness), color);
                bottom = sf::Vertex(sf::Vector2f(x, y - lineThickness), color);

                plot.append(bottom);
                plot.append(top);
            }
        }
        n++;
        returns.push_back(plot);
    }

    return returns;
}

void Canvas::shift(sf::RenderWindow &window, sf::Vector2i oldPosition, sf::Vector2i newPosition) {
    //get window size
    auto size = window.getSize();
    //scaling factor to transform mouse change coordination to number between 0 and 12 for x-axis and 0 and 10 for y-axis
    auto scale = static_cast<float>(size.y)-static_cast<float>(size.y)/13.5f;

    auto changeOfPosition = newPosition - oldPosition;

    float xChange = static_cast<float>(changeOfPosition.x)/scale*12;
    float yChange = static_cast<float>(changeOfPosition.y)/scale*10;

    _startEndHorizontal.first -= xChange;
    _startEndHorizontal.second -= xChange;
    _startEndVertical.first += yChange;
    _startEndVertical.second += yChange;
}
