//
// Created by tosiek on 06.02.23.
//

#ifndef GRAPHING_CALCULATOR_CANVAS_H
#define GRAPHING_CALCULATOR_CANVAS_H

#include <SFML/Graphics.hpp>
#include <array>

class Canvas {
public:
    /**
     * Draws coordinate system with all functions.
     * @param window Application window.
     */
    void draw(sf::RenderWindow& window);

private:
    /*
     * Vertical lines of coordinate system.
     */
    std::array<sf::RectangleShape, 11> _verticalLines;
    /**
     * Horizontal lines of coordinate system.
     */
    std::array<sf::RectangleShape, 11> _horizontalLines;

    /**
     * Sets proper position of coordinate system (relatively to window size).
     * @param window Application window.
     */
    void set_lines(sf::RenderWindow& window);
};


#endif //GRAPHING_CALCULATOR_CANVAS_H
