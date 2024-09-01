//
// Created by tosiek on 06.02.23.
//

#include "canvas.h"

#include "imgui.h"

namespace {
    float mapToInterval(float x, const float intervalRatio, const float goalMin, const float currentMin) {
        x -= currentMin;
        x /= intervalRatio;
        x += goalMin;
        return x;
    }

    // Evaluate all functions for given x
    std::vector<float> evaluateFunctions(const std::vector<std::string>& functions, const float x) {
        std::vector<float> result;
        for (const auto& function: functions) {
            auto const f = az::parse_expression(function);
            result.push_back(static_cast<float>(f->evaluate(x)));
        }
        return result;
    }

    float canvasCenter(const float height) {
        const float headerSize = height / 13.5f;
        const float canvasSize = height - headerSize;
        return canvasSize / 2.f + headerSize;
    }
}

void Canvas::draw(sf::RenderWindow& window) {
    set_lines(window);

    for (const auto& i: _verticalLines) {
        window.draw(i);
    }

    for (const auto& j: _horizontalLines) {
        window.draw(j);
    }

    for (const auto& x: prepareGraphs(window)) {
        window.draw(x);
    }
}

void Canvas::set_lines(sf::RenderWindow& window) {
    const float x = static_cast<float>(window.getSize().x);
    const float y = static_cast<float>(window.getSize().y);

    // width of the coordinate system
    const float graphWidth = x - x / 3.f;

    // y position of lines and x position of starting vertical line
    const float verticalLineY = y / 13.5f;
    float step = graphWidth / 12.f;
    float whole = std::abs(intervalX.second - std::floor(intervalX.second));
    float verticalStartX = x / 3.f + (1 - whole) * step;

    // x position of lines and y position of starting horizontal line
    const float horizontalLineX = x / 3.f;
    whole = std::abs(intervalY.second - std::floor(intervalY.second));
    float horizontalStartY = y / 13.5f + whole * step;

    // line size
    const auto verticalLineSize = sf::Vector2f(1, y - y / 13.5f);
    const auto verticalLineSizeBolded = sf::Vector2f(3, y - y / 13.5f);
    const auto horizontalLineSize = sf::Vector2f(graphWidth, 1);
    const auto horizontalLineSizeBolded = sf::Vector2f(graphWidth, 3);

    int a = 0;
    for (auto& i: _verticalLines) {
        const int zero = static_cast<int>(std::ceil(-intervalX.first)) - 1;
        sf::Vector2f size = a == zero ? verticalLineSizeBolded : verticalLineSize;
        float posX = a == zero ? verticalStartX - 1 : verticalStartX;
        sf::Color color = a == zero ? sf::Color::Black : sf::Color(150, 150, 150);
        i = sf::RectangleShape(size);
        i.setPosition(posX, verticalLineY);
        verticalStartX += step;
        i.setFillColor(color);
        a++;
    }

    int b = 0;
    for (auto& j: _horizontalLines) {
        const int zero = static_cast<int>(std::floor(intervalY.second));
        sf::Vector2f size = b == zero ? horizontalLineSizeBolded : horizontalLineSize;
        float posY = b == zero ? horizontalStartY - 1 : horizontalStartY;
        sf::Color color = b == zero ? sf::Color::Black : sf::Color(150, 150, 150);
        j = sf::RectangleShape(size);
        j.setPosition(horizontalLineX, posY);
        horizontalStartY += step;
        j.setFillColor(color);
        b++;
    }
}

std::vector<std::string>& Canvas::all_functions() {
    return functions;
}

void Canvas::show_scale(sf::RenderWindow& window) {
    //windows size
    const float x = static_cast<float>(window.getSize().x);
    const float y = static_cast<float>(window.getSize().y);

    ImGui::SetNextWindowSize(ImVec2(x / 10.f, y / 22.f));
    ImGui::SetNextWindowPos(ImVec2(x - x / 6.f, y - y / 10.f));

    constexpr int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    ImGui::Begin("Scale", nullptr, flags);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
    _scalingStep = _scale < 1.f ? 0.01f : 0.1f;
    ImGui::InputScalar("Scale", ImGuiDataType_Float, &_scale, &_scalingStep, nullptr, "%.2f");
    ImGui::PopFont();
    ImGui::End();

    // Limitation for scale
    if (_scale < 0.01f) {
        _scale = 0.01f;
    }
}

void Canvas::show_numbers(sf::RenderWindow& window) const {
    const float x = static_cast<float>(window.getSize().x);
    const float y = static_cast<float>(window.getSize().y);

    // width of the coordinate system
    const float graphWidth = x - x / 3.f;

    const float step = graphWidth / 12.f;

    // vertical numbers
    vertical_numbers(x, graphWidth, step, y);

    // horizontal numbers
    horizontal_numbers(x, step, y);
}

void Canvas::vertical_numbers(const float x, const float graphWidth, const float step, const float y) const {
    float whole;
    const float fraction = std::modf(intervalY.second, &whole);
    for (int i = 0; i < 11; ++i) {
        const auto j = static_cast<float>(i);
        float shift = std::abs(intervalX.first) - 6.f;

        ImGui::SetNextWindowSize(ImVec2(0, 0));
        auto defaultNext = ImVec2(x / 3.f + graphWidth / 2.f + shift * step, y / 13.5f + (j + fraction) * step - 18.f);
        if (intervalX.first >= 0) {
            defaultNext = ImVec2(x / 3.f, y / 13.5f + (j + fraction) * step - 18.f);
        }
        if (intervalX.second <= 0.5) {
            defaultNext = ImVec2(x - 70.f, y / 13.5f + (j + fraction) * step - 18.f);
        }
        ImGui::SetNextWindowPos(defaultNext);

        constexpr int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;

        std::string title = "Vertical number" + std::to_string(i);
        if (const float number = (whole - j) / _scale; number != 0) {
            std::string convertedNumber = std::to_string(number);
            const int afterComa = _scale > 1 ? 4 : 3;
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
    float whole;
    const float fraction = std::modf(intervalX.first, &whole);
    for (int i = 0; i <= _verticalLines.size(); ++i) {
        const auto j = static_cast<float>(i);
        float shift = std::abs(intervalY.second) - 5.f;

        ImGui::SetNextWindowSize(ImVec2(0, 0));
        auto defaultNext = ImVec2(x / 3.f + (j - fraction) * step - 24.f, y / 13.5f + y / 2.f - 18.f + shift * step);
        if (intervalY.second <= 0) {
            defaultNext = ImVec2(x / 3.f + (j - fraction) * step - 24.f, y / 13.5f);
        }
        if (intervalY.first >= -1) {
            defaultNext = ImVec2(x / 3.f + (j - fraction) * step - 24.f, y - 32.f);
        }
        ImGui::SetNextWindowPos(defaultNext);

        constexpr int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;

        std::string title = "Horizontal number" + std::to_string(i);
        const float number = (whole + j) / _scale;

        std::string convertedNumber;
        if (number == 0) {
            convertedNumber = "0";
        } else {
            convertedNumber = std::to_string(number);
            const int afterComa = _scale > 1 ? 4 : 3;
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
    for (std::string& func: this->functions) {
        auto const function = az::parse_expression(func);
        std::array<std::pair<float, float>, pointNumber> array;
        for (int i = 0; i < pointNumber; ++i) {
            const auto j = static_cast<float>(i);
            float x = intervalX.first / _scale + 12.f / static_cast<float>(pointNumber) / _scale * j;
            auto y = static_cast<float>(function->evaluate(x));
            array[i] = std::make_pair(x, y);
        }
        functions.push_back(array);
    }
    return functions;
}

std::vector<sf::VertexArray> Canvas::prepare_graphs(sf::RenderWindow& window) {
    std::vector<sf::VertexArray> returns;

    // calculating graph width
    auto width = static_cast<float>(window.getSize().x);
    const auto height = static_cast<float>(window.getSize().y);
    width = width - width / 3.f;
    const float step = width / 12.f;

    // scaling factor
    const float a = width / 12.f * _scale;

    // shifting coefficient
    const float b = width / 2.f;

    // vertical shift
    const float defaultZero = height / 13.5f + 5 * step;
    const float shift = step * (intervalY.first + intervalY.second) / 2;
    const float z = defaultZero + shift;

    auto functionsValues = evaluate_functions();

    int n = 0;
    for (const auto& i: functionsValues) {
        sf::VertexArray plot(sf::TriangleStrip);
        for (auto [x, y]: i) {
            if (!isnanf(y)) {
                x -= intervalX.first / _scale;

                // scale values
                x *= a;
                y *= -a;

                // shift graph
                x += b;
                y += z;

                sf::Vertex top, bottom;
                sf::Vertex topLeft, bottomLeft, topRight, bottomRight;
                auto color = _functionColors[n % 7];

                constexpr float lineThickness = 3.f;


                // topLeft = sf::Vertex(sf::Vector2f(x - lineThickness , y - lineThickness), color);
                // bottomLeft = sf::Vertex(sf::Vector2f(x - lineThickness , y + lineThickness), color);
                // topRight = sf::Vertex(sf::Vector2f(x + lineThickness , y - lineThickness), color);
                // bottomRight = sf::Vertex(sf::Vector2f(x + lineThickness , y + lineThickness), color);
                //
                // plot.append(bottomLeft);
                // plot.append(bottomRight);
                // plot.append(topLeft);
                // plot.append(topRight);
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

std::vector<sf::VertexArray> Canvas::prepareGraphs(sf::RenderWindow const& window) {
    std::vector graphs(functions.size(), sf::VertexArray(sf::TrianglesStrip));

    const unsigned width = window.getSize().x;
    unsigned pixel = (width + 2) / 3;
    const auto leftMargin = static_cast<float>(pixel);

    const float goalWidth = 12.f / _scale;
    const float ratio = (static_cast<float>(width) - leftMargin) / goalWidth;

    const float centerY = canvasCenter(static_cast<float>(window.getSize().y));
    auto mapForCanvas = [ratio=-1.f / ratio, interval=intervalX, centerY](float value) {
        const float min = interval.first + (interval.second - interval.first) / 2.f;
        value = mapToInterval(value, ratio, centerY, min);
        return value;
    };

    for (; pixel < width; ++pixel) {
        const auto fPixel = static_cast<float>(pixel);
        const float x = mapToInterval(static_cast<float>(pixel), ratio, intervalX.first,
                                      leftMargin);
        auto functionValues = evaluateFunctions(functions, x);

        std::vector<float> y(functions.size());
        std::ranges::transform(functionValues, y.begin(), mapForCanvas);
        for (size_t i{}; i < functions.size(); ++i) {
            const auto color = _functionColors[i % 7];
            constexpr float lineThickness = 5.f;
            graphs[i].append(sf::Vertex(sf::Vector2f(fPixel, y[i] + lineThickness), color));
            graphs[i].append(sf::Vertex(sf::Vector2f(fPixel, y[i] - lineThickness), color));
        }
    }

    return graphs;
}

void Canvas::shift(sf::RenderWindow& window, sf::Vector2i oldPosition, sf::Vector2i newPosition) {
    //get window size
    const auto size = window.getSize();
    //scaling factor to transform mouse change coordination to number between 0 and 12 for x-axis and 0 and 10 for y-axis
    const auto scale = static_cast<float>(size.y) - static_cast<float>(size.y) / 13.5f;

    const auto changeOfPosition = newPosition - oldPosition;

    const float xChange = static_cast<float>(changeOfPosition.x) / scale * 12;
    const float yChange = static_cast<float>(changeOfPosition.y) / scale * 10;

    intervalX.first -= xChange;
    intervalX.second -= xChange;
    intervalY.first += yChange;
    intervalY.second += yChange;
}
