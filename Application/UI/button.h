//
// Created by tosiek on 11.06.22.
//

#ifndef GRAPHING_CALCULATOR_BUTTON_H
#define GRAPHING_CALCULATOR_BUTTON_H

#include <SFML/Graphics.hpp>

#include "caption.h"

/**
 * Class responsible for doing stuff related with button.
 */
class Button{
    /**
     * Button's texture_.
     */
    sf::Texture texture_;

    /**
     * Button texture_ when focused_.
     */
    sf::Texture texture_f_;

    /**
     * Button's sprite_.
     */
    sf::Sprite sprite_;

    /**
     * Button's caption_.
     */
    Caption caption_;

public:
    /**
     * Constructor.
     */
    Button();

    /**
     * Sprite getter.
     * @return this->sprite_.
     */
    sf::Sprite getSprite() const { return sprite_; }

    /**
     * Caption getter.
     * @return Text of button caption_.
     */
    sf::Text getCaption() const { return caption_.getText(); }

    /**
     * Function to create button.
     * @param pos Button position.
     * @param scale Button scale_(at start size of button is 500x150);
     * @param text Text that will be set on button.
     */
    void create_button(sf::Vector2f pos, sf::Vector2f scale, const std::string& text);

    /**
     * Function to react when button is focused_.
     * @param mouse_pos Position of mouse on the screen
     * @param cursor Cursor to change if needed.
     * @param window Window on which cursor will be displayed.
     */
    bool is_focused(const sf::Vector2i& mouse_pos, sf::Cursor& cursor, sf::RenderWindow& window);
};


#endif //GRAPHING_CALCULATOR_BUTTON_H
