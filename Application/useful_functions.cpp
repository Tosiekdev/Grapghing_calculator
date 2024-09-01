//
// Created by tosiek on 05.02.23.
//

#include "useful_functions.hpp"

#include "imgui.h"

void text_centered(const std::string& text) {
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text("%s", text.c_str());
}
