//
// Created by tosiek on 05.02.23.
//

#include "function_tools.h"

void FunctionTools::show(sf::RenderWindow& window, Scene& scene) {
    //Getting window's size for scaling
    auto size = window.getSize();
    auto x = static_cast<float>(size.x);
    auto y = static_cast<float>(size.y);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(0,y/13.5f));
    ImGui::SetNextWindowSize(ImVec2(x/3.f,y-y/13.5f));

    //Color theme
    ImGui::StyleColorsLight();

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

    ImGui::Begin("Function tools", nullptr, flags);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

    text_input();
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
    if (ImGui::TreeNode("Functions"))
    {
        //static int selected = -1;
        int n = 0;
        //list all function
        for (std::string& buf:_coordinateSystem.all_functions())
        {
            if (ImGui::Selectable(buf.c_str(), _selected == n)) {
                _selected = n;
            }
            n++;
        }
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
        //delete selected function
        if (ImGui::Button("Delete")) {
            _coordinateSystem.all_functions().erase(_coordinateSystem.all_functions().cbegin() + _selected);
        }
        ImGui::PopStyleVar();
        ImGui::TreePop();
    }
}

void FunctionTools::plot_button(float x, float y) {
    ImVec2 buttonSize = ImVec2(x/12.f,y/24.f);

    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    if (ImGui::Button("Plot", buttonSize)) {
        if (_input[0] != 0 && _input[0] != ' ') {
            _coordinateSystem.all_functions().emplace_back(_input);

            for (char &i: _input) {
                i = 0;
            }
        }
    }

    ImGui::PopStyleVar();
}

void FunctionTools::show_canvas(sf::RenderWindow &window) {
    _coordinateSystem.draw(window);
}

void FunctionTools::show_scale(sf::RenderWindow &window) {
    _coordinateSystem.show_scale(window);
}

void FunctionTools::show_numbers(sf::RenderWindow &window) {
    _coordinateSystem.show_numbers(window);
}

void FunctionTools::scroll_scale(float delta) {
    _coordinateSystem.scroll_scale(delta);
}

void FunctionTools::more_about_function() {
    ImGui::Text("Argument: ");
    ImGui::SameLine();
    ImGui::InputScalar(" ",ImGuiDataType_Float,&_x,nullptr,nullptr,"%.2f");

    if (ImGui::Button("Calculate") && _selected != -1) {
        std::string function = _coordinateSystem.all_functions()[_selected];
        az::Function f;
        f.start(function);
        _f = static_cast<float>(f.calc_value(_x));
    }

    ImGui::Spacing();
    if (!std::isnan(_f)) {
        std::string text = "f(x) = " + std::to_string(_f);
        ImGui::Text("%s", text.c_str());
    }
}
