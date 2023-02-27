//
// Created by tosiek on 06.02.23.
//

#ifndef GRAPHING_CALCULATOR_CANVAS_H
#define GRAPHING_CALCULATOR_CANVAS_H

#include <SFML/Graphics.hpp>
#include <array>
#include <utility>

#include "imgui.h"
#include "imgui-SFML.h"
#include "azmath.h"

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

    /**
     * Shows scale indicator of plot;
     * @param window Application's window.
     */
    void show_scale(sf::RenderWindow &window);

    /**
     * Shows proper for scale numbers on the coordinate system;
     * @param window Application's window.
     */
    void show_numbers(sf::RenderWindow &window) const;

    /**
     * Changes _scale if mouse scrolled.
     * @param delta Wheel offset.
     */
    void scroll_scale(float delta);

    /**
     * Shifts coordinate system
     * @param window application's window
     */
    void shift(sf::RenderWindow &window, sf::Vector2i oldPosition, sf::Vector2i newPosition);

private:
    static constexpr size_t pointNumber = 1000;
    /**
     * Defines scale of plot.
     */
    float _scale = 1.f;
    /**
     * Step for increasing/decreasing scale
     */
    float _scalingStep = 0.1f;
    /**
     * Interval of visible y axis.
     */
    std::pair<float, float> _startEndVertical = std::make_pair(-5.f,5.f);
    /**
     * Interval of visible x axis.
     */
    std::pair<float, float> _startEndHorizontal = std::make_pair(-6.f,6.f);
    /*
     * Vertical lines of coordinate system.
     */
    std::array<sf::RectangleShape, 12> _verticalLines;
    /**
     * Horizontal lines of coordinate system.
     */
    std::array<sf::RectangleShape, 11> _horizontalLines;
    /**
     * Stores definitions of all functions.
     */
    std::vector<std::string> _allFunctions;

    const std::array<sf::Color, 7> _functionColors= {
            sf::Color::Black,
            sf::Color::Blue,
            sf::Color::Magenta,
            sf::Color::Yellow,
            sf::Color::Green,
            sf::Color::Red,
            sf::Color::Cyan
    };

    /**
     * Sets proper position of coordinate system (relatively to window size).
     * @param window Application window.
     */
    void set_lines(sf::RenderWindow& window);

    /**
     * Draws vertical numbers on coordinate system.
     * @param x Width of the window.
     * @param graphWidth Width of the coordinate system.
     * @param step Size of the space between lines.
     * @param y Height of the window.
     */
    void vertical_numbers(float x, float graphWidth, float step, float y) const;
    /**
     * Draws horizontal numbers on coordinate system.
     * @param x Width of the window.
     * @param step Size of the space between lines.
     * @param y Height of the window.
     */
    void horizontal_numbers(float x, float step, float y) const;

    /**
     * Calculates value of all functions on visible interval.
     * @return 1000 coordinates of points which are subset of function.
     */
    std::vector<std::array<std::pair<float, float>, pointNumber>> evaluate_functions();

    /**
     * Calculates positions of points to draw graph.
     * @return Vector of vertex arrays in type sf::TriangleStrip.
     */
    std::vector<sf::VertexArray> prepare_graphs(sf::RenderWindow &window);
};


#endif //GRAPHING_CALCULATOR_CANVAS_H
