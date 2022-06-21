//
// Created by tosiek on 14.06.22.
//

#ifndef GRAPHING_CALCULATOR_GRAPH_H
#define GRAPHING_CALCULATOR_GRAPH_H

#include <array>
#include <string>

#include "plot.h"
#include "UI/caption.h"
#include "UI/button.h"

class Graph{
    /**
     * Background of the graph.
     */
     sf::RectangleShape graph_;

     /**
      * Vertical lines on graph.
      */
     std::array<sf::RectangleShape,19> vertical_lines;

    /**
     * Horizontal lines on graph.
     */
    std::array<sf::RectangleShape,19> horizontal_lines;

    /**
     * How much numbers will fit on graph.
     */
    int scale_{};

    /**
     * Numbers near x-axis.
     */
     std::array<Caption,21> x_nums;

    /**
    * Numbers near y-axis.
    */
    std::array<Caption,21> y_nums;

    /**
     * Functions' plots.
     */
     std::array<Plot,7> functions_;

     /**
      * Functions' expressions.
      */
     std::array<std::string, 7> func_expr_;

public:
    /**
     * Constructor.
     */
    Graph();

    /**
     * Function to set position.
     * @param pos New position of graph.
     */
    void set_position(sf::Vector2f pos);

    /**
     * Function to draw whole graph.
     * @param window Window on which graph will be drew.
     */
    void draw(sf::RenderWindow& window);

    /**
     * Function to setting graph scale_.
     * @param scale New graph scale_.
     */
    void set_scale(int scale);

    /**
     * Function to create plot function.
     * @param expr Function to plot.
     */
    size_t create_plot(const std::string& expr);

    /**
     * Operator [] to get function from graph.
     * @param pos Function position.
     * @return Function from graph at certain position.
     */
    std::string& operator[](size_t pos) { return func_expr_[pos]; }

    /**
     * Deletes function at certain index.
     * @param i Index of function which will be deleted.
     */
    void delete_function(size_t i);

    /**
     * Calculates certain value for certain argument.
     * @param i Function index.
     * @param x Argument.
     * @return Calculated value.
     */
    double calc_value(size_t i, double x) { return functions_[i].calc_value(x); }
};


#endif //GRAPHING_CALCULATOR_GRAPH_H
