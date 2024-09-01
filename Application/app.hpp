//
// Created by tosiek on 11.06.22.
//

#ifndef GRAPHING_CALCULATOR_APP_H
#define GRAPHING_CALCULATOR_APP_H

#include "calculator.hpp"
#include "manual.hpp"
#include "menu.hpp"

/**
 * Class responsible for whole application.
 */
class App {
 /**
  * Menu scene.
  */
 Menu menu_;

 /**
  * Calculator scene.
  */
 Calculator calculator_;

 /**
  * Manual scene.
  */
 Manual manual_;

 /**
  * Enum type to manage current scene.
  */
 Scene current_;

 /**
  * Main window of program.
  */
 sf::RenderWindow window_;

 static constexpr auto fontPath = "OpenSans-VariableFont_wdth,wght.ttf";

public:
 /**
  * Constructor.
  */
 App();

 /**
  * Function to start application, show window, and handle scenes.
  */
 void start();
};


#endif //GRAPHING_CALCULATOR_APP_H
