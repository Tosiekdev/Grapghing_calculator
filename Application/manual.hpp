//
// Created by tosiek on 16.06.22.
//

#ifndef GRAPHING_CALCULATOR_MANUAL_H
#define GRAPHING_CALCULATOR_MANUAL_H

#include "window.hpp"

class Manual : public Window {
 /**
  * Shows information about application.
  * @param window Application window.
  * @param scene Application scene.
  */
 static void help(sf::RenderWindow& window, Scene& scene);

public:
 /**
  * Function to handle events in calculator.
  * @param window Window from which events will be handled.
  */
 void handle_events(sf::RenderWindow& window, Scene& scene) override;

 /**
  * Function to do some necessary things between frames.
  * @param window Window, maybe will be used.
  */
 void do_stuff(sf::RenderWindow& window, sf::Clock& deltaClock, Scene& scene) override;

 /**
  * Function to display buttons etc.
  * @param window Window where content will be displayed.
  */
 void display(sf::RenderWindow& window) override;
};


#endif //GRAPHING_CALCULATOR_MANUAL_H
