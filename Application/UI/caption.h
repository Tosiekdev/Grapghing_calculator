//
// Created by tosiek on 13.06.22.
//

#ifndef GRAPHING_CALCULATOR_CAPTION_H
#define GRAPHING_CALCULATOR_CAPTION_H

#include <SFML/Graphics.hpp>
#include <string>

/**
 * Class to combine Font with Text.
 */
class Caption{
    /**
     * Font for caption_.
     */
    sf::Font font;

    /**
     * Text of caption_.
     */
    sf::Text text;

    /**
     * Special function to set caption_ origin to center;
     */
    void setCenter();
public:
    /**
     * Text getter
     * @return this->text.
     */
    sf::Text getText() const { return text; }

    /**
     * Function to load font from file and set it to the text.
     * @param path
     */
    void loadFromFile(const std::string& path);

    /**
     * Function to set position to the text.
     * @param pos New position.
     */
    void setPosition(sf::Vector2f pos) { text.setPosition(pos); }

    /**
     * Function to set string to the text.
     * @param caption New caption_.
     */
    void setString(const std::string& caption);

    /**
     * Function to set character size.
     * @param size New size.
     */
    void setCharacterSize(unsigned int size);

    /**
     * Function to set color.
     * @param color New color.
     */
    void setFillColor(sf::Color color) { text.setFillColor(color); }

    /**
     * Function to set text origin.
     * @param origin New origin.
     */
    void setOrigin(sf::Vector2f origin) { text.setOrigin(origin); }
};


#endif //GRAPHING_CALCULATOR_CAPTION_H
