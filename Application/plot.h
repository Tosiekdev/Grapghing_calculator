//
// Created by tosiek on 14.06.22.
//

#ifndef GRAPHING_CALCULATOR_PLOT_H
#define GRAPHING_CALCULATOR_PLOT_H

#include <array>
#include <map>
#include <SFML/Graphics.hpp>
#include <limits>

#include "azmath.h"

class Plot{
    static constexpr size_t prc=500;

    /**
     * Map numbers to colors for plot color.
     */
     std::array<sf::Color, 7> _colors = {
            sf::Color::Black,
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Magenta,
            sf::Color::Cyan
     };

    /**
     * Function counter.
     */
     static int count_;

    /**
     * Function which will be plotted.
     */
     az::Function function_;

    /**
     * Array of all needed values for scale 1.
     */
     std::array<double, prc + 1> values1_{};
    /**
     * Array of all needed values for scale 10.
     */
     std::array<double, prc + 1> values10_{};
    /**
     * Array of all needed values for scale 100.
     */
     std::array<double, prc + 1> values100_{};

     /**
      * Lines of the plot for scale 1.
      */
      std::array<sf::VertexArray,prc> lines1_;
     /**
      * Lines of the plot for scale 10.
      */
      std::array<sf::VertexArray,prc> lines10_;
      /**
       * Lines of the plot for scale 100.
       */
      std::array<sf::VertexArray,prc> lines100_;

      /**
       * Function to calculate values.
       * @param values Proper array of values.
       * @param scale Proper scale.
       * @param lines Proper lines.
       */
      void calc_values(std::array<double, prc+1>&values,int scale,std::array<sf::VertexArray,prc>&lines,sf::Vector2f pos);

public:
    /**
     * Constructor.
     */
    Plot();

    /**
     * Creates function plot.
     * @param expr Expression from which function is evaluated.
     * @param scale Scale set on graph.
     * @param position Position of graph on the screen.
     */
    void create_plot(const std::string& expr, sf::Vector2f position);

    /**
     * Function to draw function plot.
     * @param window Window on which function will be displayed.
     */
    void draw(sf::RenderWindow& window, int scale);

    /**
     * Clears all lines.
     * @param pos Position of graph.
     */
    void clear(sf::Vector2f pos);

    /**
     * Calculates value for certain x.
     * @param x Argument to calculate function.
     * @return Calculated value.
     */
    double calc_value(double x);
};

#endif //GRAPHING_CALCULATOR_PLOT_H
