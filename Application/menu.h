//
// Created by tosiek on 11.06.22.
//

#ifndef GRAPHING_CALCULATOR_MENU_H
#define GRAPHING_CALCULATOR_MENU_H

#include "window.h"
#include "UI/object.h"
#include "UI/caption.h"
#include "UI/button.h"

class Menu : public Window{
    /**
     * Button to go into calculator_.
     */
    Button calculator_;

    /**
     * Button to get know how to use calculator_.
     */
    Button manual_;

    /**
     * Button to exit_.
     */
    Button exit_;

    /**
     * Sets and display beautiful control menu buttons.
     */
    void menuOptions(sf::RenderWindow &window, sf::Clock deltaClock, Scene &scene);

public:
    /**
     * Constructor.
     */
    Menu();

    /**
     * Function to handle events in menu.
     * @param window Window from which events will be handled.
     */
    void handle_events(sf::RenderWindow &window, Scene &scene) override;

    /**
     * Function to do some necessary things between frames.
     * @param window Window, maybe will be used.
     */
    void do_stuff(sf::RenderWindow &window, sf::Clock deltaClock, Scene &scene) override;

     /**
      * Function to display buttons etc.
      * @param window Window where content will be displayed.
      */
     void display(sf::RenderWindow& window) override;
};


#endif //GRAPHING_CALCULATOR_MENU_H
