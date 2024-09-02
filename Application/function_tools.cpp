//
// Created by tosiek on 05.02.23.
//

#include "function_tools.hpp"

void FunctionTools::show(sf::RenderWindow& window, Scene& scene) {
    //Getting window's size for scaling
    const auto size = window.getSize();
    const auto x = static_cast<float>(size.x);
    const auto y = static_cast<float>(size.y);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(0, y / 13.5f));
    ImGui::SetNextWindowSize(ImVec2(x / 3.f, y - y / 13.5f));

    //Color theme
    ImGui::StyleColorsLight();

    constexpr int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

    ImGui::Begin("Function tools", nullptr, flags);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

    text_input();
    if (!_errorMsg.empty()) {
        ImGui::Text(_errorMsg.c_str());
    }
    ImGui::Spacing();
    plot_button(x, y);
    ImGui::Spacing();
    functions_list();
    ImGui::Spacing();
    more_about_function();

    ImGui::PopFont();

    ImGui::End();
}

void FunctionTools::text_input() {
    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    ImGui::InputText(" f(x)", _input, sizeof(_input));

    ImGui::PopStyleVar();
}

void FunctionTools::functions_list() {
    if (ImGui::TreeNodeEx("Functions", ImGuiTreeNodeFlags_DefaultOpen)) {
        //static int selected = -1;
        int n = 0;
        //list all function
        for (std::string& buf: _coordinateSystem.functions) {
            if (ImGui::Selectable(buf.c_str(), _selected == n)) {
                _selected = n;
            }
            n++;
        }
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
        //delete selected function
        if (ImGui::Button("Delete")) {
            _coordinateSystem.functions.erase(_coordinateSystem.functions.cbegin() + _selected);
        }
        ImGui::PopStyleVar();
        ImGui::TreePop();
    }
}

void FunctionTools::plot_button(const float x, const float y) {
    const auto buttonSize = ImVec2(x / 12.f, y / 24.f);

    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    if (ImGui::Button("Plot", buttonSize)) {
        add_function();
    }

    ImGui::PopStyleVar();
}

void FunctionTools::show_canvas(sf::RenderWindow& window) {
    _coordinateSystem.draw(window);
}

void FunctionTools::show_scale(sf::RenderWindow& window) {
    _coordinateSystem.showScale(window);
}

void FunctionTools::show_numbers(sf::RenderWindow& window) const {
    _coordinateSystem.showNumbers(window);
}

void FunctionTools::scroll_scale(const float delta) {
    _coordinateSystem.scrollScale(delta);
}

void FunctionTools::more_about_function() {
    ImGui::Text("Argument: ");
    ImGui::SameLine();
    ImGui::InputScalar(" ", ImGuiDataType_Float, &_x, nullptr, nullptr, "%.2f");

    if (ImGui::Button("Calculate") && _selected != -1) {
        std::string const& function = _coordinateSystem.functions.at(_selected);
        auto const f = az::parse_expression(function);
        _f = static_cast<float>(f->evaluate(_x));
    }

    ImGui::Spacing();
    if (!std::isnan(_f)) {
        std::string const text = "f(x) = " + std::to_string(_f);
        ImGui::Text("%s", text.c_str());
    }
}

void FunctionTools::add_function() {
    if (az::parse_expression(_input)) {
        _coordinateSystem.functions.emplace_back(_input);
        _errorMsg.clear();
    } else {
        _errorMsg = "Invalid expression!";
    }
}

void FunctionTools::shift_graph(sf::RenderWindow& window, const sf::Vector2i oldPosition, const sf::Vector2i newPosition) {
    _coordinateSystem.shift(window, oldPosition, newPosition);
}
