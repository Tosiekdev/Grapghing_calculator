//
// Created by tosiek on 15.06.22.
//

#ifndef GRAPHING_CALCULATOR_TEXTBOX_H
#define GRAPHING_CALCULATOR_TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

#include "caption.h"

class Textbox{
    /**
     * Current position of indicator_.
     */
    size_t indicator_;

    /**
     * Entered text.
     */
    std::string content_;

    /**
     * Focused text
     */
    std::string view_text_;

    /**
     * Text with entered text and '_' at the end.
     */
    Caption view_;

    /**
     * State of textbox.
     */
    bool focused_;

    /**
     * Texture of textbox.
     */
    sf::Texture texture_;

    /**
     * Texture's sprite.
     */
     sf::Sprite sprite_;

public:
    /**
     * Constructor.
     */
    Textbox();

    /**
     * Focused getter
     * @return If textbox is focused_.
     */
    bool is_focused() const { return focused_; }

    /**
     * Function to focus/not-focus textbox.
     * @param state State of textbox.
     */
    void focus(bool state);

    /**
     * Add character to content.
     * @param sign Character to add.
     */
    void update(char sign);

    /**
     * Function to check if mouse is over textbox.
     * @param mouse Mouse position.
     * @param cursor Cursor to change texture_.
     * @return Whether mouse is above textbox or not.
     */
    bool mouse_above(sf::Vector2i mouse, sf::Cursor& cursor, sf::RenderWindow& window);

    /**
     * Erases last element of content.
     */
    void erase();

    /**
     * Function to set textbox position.
     * @param pos Position of textbox.
     */
    void create_textbox(sf::Vector2f pos, sf::Vector2f scale);

    /**
     * Function to draw while textbox.
     * @param window Window where textbox is draw.
     */
    void draw(sf::RenderWindow& window);

    /**
     * Function to get text from textbox.
     * @return Content.
     */
    std::string get_content() { return content_; }

    /**
     * Clears textbox.
     */
    void clear();

    /**
     * Function to move indicator.
     * @param direction -1 if to left, 1 if to right.
     */
    void move_indicator(int direction);
};


#endif //GRAPHING_CALCULATOR_TEXTBOX_H
