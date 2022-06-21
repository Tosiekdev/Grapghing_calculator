//
// Created by tosiek on 12.06.22.
//

#include "object.h"

void Object::loadFromFile(const std::string& path){
    texture.loadFromFile(path);
    sprite.setTexture(texture);
}
