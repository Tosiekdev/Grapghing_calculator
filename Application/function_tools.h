//
// Created by tosiek on 05.02.23.
//

#ifndef GRAPHING_CALCULATOR_FUNCTIONTOOLS_H
#define GRAPHING_CALCULATOR_FUNCTIONTOOLS_H

#include <SFML/Graphics.hpp>
#include <array>

#include "imgui.h"
#include "imgui-SFML.h"
#include "window.h"

class FunctionTools {
public:
    void show(sf::RenderWindow &window, Scene &scene);

private:
    char _input[1024]="";
    std::vector<std::string> _allFunctions;

    /**
     * Input space for function formula.
     */
    void textInput();
    /**
     * Shows all plotted functions.
     */
    void functionsList();
    /**
     * Button to plot function from input text.
     * @param x Width of the window.
     * @param y Height of the window.
     */
    void plotButton(float x, float y);
};


#endif //GRAPHING_CALCULATOR_FUNCTIONTOOLS_H