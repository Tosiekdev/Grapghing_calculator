//
// Created by tosiek on 11.06.22.
//

#ifndef GRAPHING_CALCULATOR_WINDOW_H
#define GRAPHING_CALCULATOR_WINDOW_H

#include <SFML/Graphics.hpp>

enum Scene { MENU, CALCULATOR, INSTRUCTION };

/**
 * Virtual class. Is used as a template for app scenes.
 */
class Window {
public:
 virtual ~Window() = default;

protected:
 /**
  * Event to handling.
  */
 sf::Event e_{};

 /**
  * To tell if any of buttons is focused_.
  */
 bool is_focused{};

 /**
  * Cursor used in menu.
  */
 sf::Cursor cursor_;

 /**
  * Displays button which takes user back to the menu.
  * @param window Display target.
  * @param deltaClock For updating ImGui.
  * @param scene Application scene.
  */
 static void returning_button(sf::RenderWindow& window, sf::Clock& deltaClock, Scene& scene);

 /**
  * Displays application title.
  * @param window Display target.
  * @param scene Application scene.
  */
 static void title(sf::RenderWindow& window, Scene& scene);

 /**
  * Displays application's background.
  * @param window App's window.
  * @param scene App's scene.
  */
 static void background(sf::RenderWindow& window, Scene& scene);

public:
 /**
  * Virtual function to handling events.
  * @param window Window from events are handled.
  */
 virtual void handle_events(sf::RenderWindow& window, Scene& scene) =0;

 /**
  * Virtual function to make some operations between frames.
  * @param window Window, maybe it will be needed.
  */
 virtual void do_stuff(sf::RenderWindow& window, sf::Clock& deltaClock, Scene& scene) =0;

 /**
  * Virtual function to display window content.
  * @param window Window where content will be displayed.
  */
 virtual void display(sf::RenderWindow& window) =0;
};


#endif //GRAPHING_CALCULATOR_WINDOW_H
