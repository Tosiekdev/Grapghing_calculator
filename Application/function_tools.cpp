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
    textInput();
    ImGui::Spacing();
    plotButton(x,y);
    ImGui::Spacing();
    functionsList();
    ImGui::PopFont();
    ImGui::End();
}

void FunctionTools::textInput() {
    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    ImGui::InputText(" f(x)", _input, sizeof(_input));

    ImGui::PopStyleVar();
}

void FunctionTools::functionsList() {
    if (ImGui::TreeNode("Functions"))
    {
        static int selected = -1;
        int n = 0;
        //list all function
        for (std::string& buf:_coordinateSystem.all_functions())
        {
            if (ImGui::Selectable(buf.c_str(), selected == n))
                selected = n;
            n++;
        }
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
        //delete selected function
        if (ImGui::Button("Delete")) {
            if (!_coordinateSystem.all_functions().empty() && selected >= 0) {
                _coordinateSystem.all_functions().erase(_coordinateSystem.all_functions().cbegin() + selected);
            }
        }
        ImGui::PopStyleVar();
        ImGui::TreePop();
    }
}

void FunctionTools::plotButton(float x, float y) {
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
