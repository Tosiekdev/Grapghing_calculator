//
// Created by tosiek on 06.02.23.
//

#ifndef GRAPHING_CALCULATOR_CANVAS_H
#define GRAPHING_CALCULATOR_CANVAS_H

#include <SFML/Graphics.hpp>
#include <array>

#include "imgui.h"
#include "imgui-SFML.h"

class Canvas {
public:
    /**
     * Draws coordinate system with all functions.
     * @param window Application window.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @return Reference to vector of all functions.
     */
    std::vector<std::string>& all_functions();

    void show_scale(sf::RenderWindow &window);

private:
    /**
     * Defines scale of plot.
     */
    float _scale = 1.f;
    /**
     * Step for increasing/decreasing scale
     */
    float _scalingStep = 0.1f;
    /*
     * Vertical lines of coordinate system.
     */
    std::array<sf::RectangleShape, 11> _verticalLines;
    /**
     * Horizontal lines of coordinate system.
     */
    std::array<sf::RectangleShape, 11> _horizontalLines;
    /**
     * Stores definitions of all functions.
     */
    std::vector<std::string> _allFunctions;

    /**
     * Sets proper position of coordinate system (relatively to window size).
     * @param window Application window.
     */
    void set_lines(sf::RenderWindow& window);
};


#endif //GRAPHING_CALCULATOR_CANVAS_H
