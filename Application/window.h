//
// Created by tosiek on 11.06.22.
//

#ifndef GRAPHING_CALCULATOR_WINDOW_H
#define GRAPHING_CALCULATOR_WINDOW_H

#include "UI/button.h"
#include "UI/object.h"

#include "imgui.h"
#include "imgui-SFML.h"

enum Scene{MENU, CALCULATOR, INSTRUCTION};

/**
 * Virtual class. Is used as a template for app scenes.
 */
class Window{
protected:
    /**
     * Button used to returning to main menu.
     */
    Button returning_;

    /**
     * Event to handling.
     */
    sf::Event e_{};

    /**
     * To tell if any of buttons is focused_.
     */
    bool is_focused;

    /**
     * Cursor used in menu.
     */
    sf::Cursor cursor_;

    /**
     * Background to the title.
     */
    Object header_;

    /**
     * Font and text to show title.
     */
    Caption title_;

public:
    /**
     * Virtual function to handling events.
     * @param window Window from events are handled.
     */
    virtual void handle_events(sf::RenderWindow &window, Scene &scene) =0;

    /**
     * Virtual function to make some operations between frames.
     * @param window Window, maybe it will be needed.
     */
    virtual void do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) =0;

    /**
     * Virtual function to display window content.
     * @param window Window where content will be displayed.
     */
     virtual void display(sf::RenderWindow& window)=0;

    /*
    * Displays button which takes user back to the menu.
    */
    static void returningButton(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene);
};


#endif //GRAPHING_CALCULATOR_WINDOW_H
