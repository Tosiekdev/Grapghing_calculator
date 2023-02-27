//
// Created by tosiek on 14.06.22.
//

#ifndef GRAPHING_CALCULATOR_CALCULATOR_H
#define GRAPHING_CALCULATOR_CALCULATOR_H

#include "window.h"
#include "function_tools.h"
#include "canvas.h"

/**
 * Class to handle graphic calculator.
 */
class Calculator : public Window{
     /**
      * Shows function tools.
      */
     FunctionTools _tools;

     sf::Vector2i _bufMousePos = sf::Vector2i(-1,-1);

public:
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
    void do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) override;

    /**
     * Function to display buttons etc.
     * @param window Window where content will be displayed.
     */
    void display(sf::RenderWindow& window) override;
};


#endif //GRAPHING_CALCULATOR_CALCULATOR_H
