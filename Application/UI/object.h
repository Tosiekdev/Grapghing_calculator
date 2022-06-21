//
// Created by tosiek on 12.06.22.
//

#ifndef GRAPHING_CALCULATOR_OBJECT_H
#define GRAPHING_CALCULATOR_OBJECT_H

#include <SFML/Graphics.hpp>

/**
 * Class to combine Sprite with Texture.
 */
class Object{
    /**
     * Texture of sprite_.
     */
    sf::Texture texture;

    /**
     * Sprite associated with texture_.
     */
    sf::Sprite sprite;

public:
    /**
     * Sprite getter.
     * @return this->sprite_.
     */
    sf::Sprite getSprite() { return sprite; }

    /**
     * Set new position of object.
     * @param pos New position.
     */
    void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); };

    /**
     * Function to load texture_ from file and assign it to the sprite_.
     * @param path Path to the file.
     */
    void loadFromFile(const std::string& path);
};


#endif //GRAPHING_CALCULATOR_OBJECT_H
