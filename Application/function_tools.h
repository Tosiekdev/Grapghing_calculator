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

    /**
     * Displays numbers on coordinate system
     * @param window Application's window.
     */
    void show_numbers(sf::RenderWindow &window);

    /**
     * Changes coordination system _scale if mouse scrolled.
     * @param delta Wheel offset.
     */
    void scroll_scale(float delta);

private:
    char _input[1024]="";
    Canvas _coordinateSystem;
    float _x = 0;
    float _f = nanf("");
    int _selected = -1;

    /**
     * Input space for function formula.
     */
    void text_input();

    /**
     * Shows all plotted functions.
     */
    void functions_list();

    /**
     * Button to plot function from input text.
     * @param x Width of the window.
     * @param y Height of the window.
     */
    void plot_button(float x, float y);

    /**
     * Gives opportunity to calculate value of the function for given argument.
     */
    void more_about_function();
};


#endif //GRAPHING_CALCULATOR_FUNCTIONTOOLS_H
