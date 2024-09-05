//
// Created by tosiek on 06.02.23.
//

#ifndef GRAPHING_CALCULATOR_CANVAS_H
#define GRAPHING_CALCULATOR_CANVAS_H

#include <SFML/Graphics.hpp>

#include <array>
#include <utility>

#include <az_math/function_parser.hpp>

#include "imgui-SFML.h"

using Interval = std::pair<float, float>;

class Canvas {
public:
 /**
  * Draws coordinate system with all functions.
  * @param window Application window.
  */
 void draw(sf::RenderWindow& window);

 /**
  * Shows scale indicator of plot;
  * @param window Application's window.
  */
 void showScale(const sf::RenderWindow& window);

 /**
  * Shows proper for scale numbers on the coordinate system;
  * @param window Application's window.
  */
 void showNumbers(const sf::RenderWindow& window) const;

 /**
  * Changes _scale if mouse scrolled.
  * @param delta Wheel offset.
  */
 void scrollScale(float delta);

 /**
  * Shifts coordinate system
  * @param window application's window
  */
 void shift(const sf::RenderWindow& window, sf::Vector2i oldPosition, sf::Vector2i newPosition);

 /**
  * @return Smallest x in visible canvas
  */
 float minX() const {
  return intervalX.first / scale;
 }

 /**
  * Stores definitions of all functions.
  */
 std::vector<std::string> functions;

private:
 /**
  * Defines scale of plot.
  */
 float scale = 1.f;
 /**
  * Step for increasing/decreasing scale
  */
 float scalingStep = 0.1f;
 /**
  * Interval of visible y axis.
  */
 Interval intervalY = std::make_pair(-5.f, 5.f);
 /**
  * Interval of visible x axis.
  */
 Interval intervalX = std::make_pair(-6.f, 6.f);
 /*
  * Vertical lines of coordinate system.
  */
 std::array<sf::RectangleShape, 13> verticalLines;
 /**
  * Horizontal lines of coordinate system.
  */
 std::array<sf::RectangleShape, 11> horizontalLines;

 const std::array<sf::Color, 7> functionColors = {
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
 void setLines(const sf::RenderWindow& window);

 /**
  * Sets proper position of coordinate system (relatively to window size and scale).
  * @param window Application window.
  */
 void setLines2(const sf::RenderWindow& window);

 void setHorizontalLines(float canvasWidth, float canvasHeight);
 void setVerticalLines(float canvasWidth, float canvasHeight);

 /**
  * Draws vertical numbers on coordinate system.
  * @param x Width of the window.
  * @param graphWidth Width of the coordinate system.
  * @param step Size of the space between lines.
  * @param y Height of the window.
  */
 void verticalNumbers(float x, float graphWidth, float step, float y) const;

 /**
  * Draws horizontal numbers on coordinate system.
  * @param x Width of the window.
  * @param step Size of the space between lines.
  * @param y Height of the window.
  */
 void horizontalNumbers(float x, float step, float y) const;

 /**
  * Calculates positions of points to draw graph.
  * @return Vector of vertex arrays in type sf::TriangleStrip.
  */
 std::vector<sf::VertexArray> prepareGraphs(sf::RenderWindow const& window) const;
};


#endif //GRAPHING_CALCULATOR_CANVAS_H
