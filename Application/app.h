//
// Created by tosiek on 11.06.22.
//

#ifndef GRAPHING_CALCULATOR_APP_H
#define GRAPHING_CALCULATOR_APP_H

#include "menu.h"
#include "calculator.h"
#include "manual.h"

/**
 * Class responsible for whole application.
 */
class App{
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
