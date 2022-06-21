//
// Created by tosiek on 13.06.22.
//

#include "caption.h"

void Caption::loadFromFile(const std::string &path){
    font.loadFromFile(path);
    text.setFont(font);
}

void Caption::setString(const std::string &caption){
    text.setString(caption);
    setCenter();
}

void Caption::setCharacterSize(unsigned int size){
    text.setCharacterSize(size);
    setCenter();
}

void Caption::setCenter(){
    auto x=text.getLocalBounds().width/2;
    auto y=text.getLocalBounds().height/2;
    text.setOrigin(x,y);
}
