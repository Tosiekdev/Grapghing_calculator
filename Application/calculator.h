//
// Created by tosiek on 14.06.22.
//

#ifndef GRAPHING_CALCULATOR_CALCULATOR_H
#define GRAPHING_CALCULATOR_CALCULATOR_H

#include "window.h"
#include "graph.h"
#include "UI/object.h"
#include "UI/caption.h"
#include "UI/button.h"
#include "UI/textbox.h"

/**
 * Class to handle graphic calculator.
 */
class Calculator : public Window{
    /**
     * Map numbers to colors for plot color.
     */
    std::map<int, sf::Color> colors{
            {0,sf::Color::Black},
            {1, sf::Color::Red},
            {2, sf::Color::Green},
            {3, sf::Color::Blue},
            {4, sf::Color::Yellow},
            {5, sf::Color::Magenta},
            {6, sf::Color::Cyan},
    };

    /**
     * Graph to graph functions.
     */
     Graph graph;
     /**
      *
      */
     Button x1_;
     /**
      * Button to set scale to 10.
      */
     Button x10_;;
     /**
      * Button to set scale to 100.
      */
     Button x100_;

     /**
      * Place to enter functions.
      */
     Textbox textbox_;

     /**
      * Caption to selected function.
      */
     Caption selected_;

     /**
      * Caption with information about textbox taking an argument.
      */
     Caption calc_for_;

     /**
      * Textbox for argument
      */
     Textbox argument_;

     /**
      * Button to remove functions.
      */
     Button remove_func_;

     /**
      * Button to calculate function value for certain x.
      */
     Button calc_;

     /**
      * Caption f(x)=calculated value.
      */
     Caption f_calculated_;

     /**
      * Textbox to enter selected function.
      */
     Textbox select_func_;

     /**
      * Caption with f(x)
      */
     Caption f_;

     /**
      * Squares responsible for legend.
      */
     std::array<sf::RectangleShape,7> func_colors_;

     /**
      * Functions formulas.
      */
     std::array<Caption, 7> func_caps_;

     /**
      * Set all textbox to not focused.
      */
     void not_focused();

public:
    /**
     * Constructor.
     */
    Calculator();

    /**
     * Function to handle events in calculator.
     * @param window Window from which events will be handled.
     * @param scene Application scenes.
     */
    void handle_events(sf::RenderWindow &window, Scene &scene) override;

    /**
     * Function to do some necessary things between frames.
     * @param window Window, maybe will be used.
     * @param deltaClock Needed for proper rendering of ImGui contents.
     */
    void do_stuff(sf::RenderWindow &window, sf::Clock deltaClock, Scene &scene) override;

    /**
     * Function to display buttons etc.
     * @param window Window where content will be displayed.
     */
    void display(sf::RenderWindow& window) override;
};


#endif //GRAPHING_CALCULATOR_CALCULATOR_H
