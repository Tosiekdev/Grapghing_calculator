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
#include "canvas.h"

class FunctionTools {
public:
    /**
     * Displays function tools.
     * @param window Application's window.
     * @param scene Application's scenes.
     */
    void show(sf::RenderWindow &window, Scene &scene);

    /**
     * Draws coordinates system and functions.
     * @param window
     */
    void show_canvas(sf::RenderWindow &window);

    /**
     * Shows controls for scale.
     * @param window Application's window.
     */
    void show_scale(sf::RenderWindow &window);

private:
    char _input[1024]="";
    Canvas _coordinateSystem;

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
