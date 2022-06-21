//
// Created by tosiek on 14.06.22.
//

#include "graph.h"

Graph::Graph(){
    set_scale(10);

    graph_.setSize(sf::Vector2f(1000, 1000));
    graph_.setFillColor(sf::Color::White);

    for(auto &i:vertical_lines){
        i.setSize(sf::Vector2f(1.f,1000.f));
        i.setFillColor(sf::Color(128,128,128));
    }
    vertical_lines[9].setSize(sf::Vector2f(3.f,1000.f));
    vertical_lines[9].setFillColor(sf::Color::Black);
    vertical_lines[9].setOrigin(1,0);

    for(auto &i:horizontal_lines){
        i.setSize(sf::Vector2f(1000.f,1.f));
        i.setFillColor(sf::Color(128,128,128));
    }
    horizontal_lines[9].setSize(sf::Vector2f(1000.f,3.f));
    horizontal_lines[9].setFillColor(sf::Color::Black);
    horizontal_lines[9].setOrigin(0,1);
}

void Graph::draw(sf::RenderWindow& window){
    window.draw(graph_);

    for(auto &i:vertical_lines) { window.draw(i); }
    for(auto &i:horizontal_lines) { window.draw(i); }
    for(auto &i:x_nums) { window.draw(i.getText()); }
    for(auto &i:y_nums) { window.draw(i.getText()); }

    for(auto &i:functions_) { i.draw(window,scale_); }
}

void Graph::set_position(sf::Vector2f pos){
    graph_.setPosition(pos);

    for(size_t i=0; i<19; i++){
        vertical_lines[i].setPosition(pos.x+static_cast<float>((i+1)*50),pos.y);
        horizontal_lines[i].setPosition(pos.x,pos.y+static_cast<float>((i+1)*50));
    }

    for(size_t i=0; i<21; i++){
        x_nums[i].setPosition(sf::Vector2f(pos.x+(float)i*50+7,pos.y+505));
    }
    x_nums[10].setPosition(sf::Vector2f(pos.x+507.f,pos.y+505.f));

    for(size_t i=0; i<21; i++){
        y_nums[i].setPosition(sf::Vector2f(pos.x+490,pos.y+(float)i*50-7));
    }
    y_nums[10].setPosition(sf::Vector2f(pos.x+493.f,pos.y+490.f));
    y_nums[0].setPosition(sf::Vector2f(pos.x+490.f,pos.y+5));

    for(auto &i:functions_) { i.clear(pos); }
    for(auto &i:func_expr_) { i="0"; }
}

void Graph::set_scale(int scale){
    scale_=scale;

    float value=-1.f;
    for(auto &i:x_nums){
        i.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
        i.setCharacterSize(10);
        if(scale_ != 1){
            std::string num=std::to_string((int)roundf((float)(value*(float)scale_)));
            i.setString(num);
        }else{
            std::string num=std::to_string((value*(float)scale_));
            num.erase(num.find_last_not_of('0')+1, std::string::npos);
            i.setString(num);
        }
        i.setFillColor(sf::Color::Black);
        value+=0.1f;
    }

    value=1.f;
    for(auto &i:y_nums){
        i.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
        i.setCharacterSize(10);
        if(scale_ != 1){
            std::string num=std::to_string((int)roundf((float)(value*(float)scale_)));
            i.setString(num);
        }else{
            std::string num=std::to_string((value*(float)scale_));
            num.erase(num.find_last_not_of('0')+1, std::string::npos);
            i.setString(num);
        }
        i.setFillColor(sf::Color::Black);
        value-=0.1f;
    }
}

size_t Graph::create_plot(const std::string& expr){
    size_t i=0;
    while(i<7 && func_expr_[i]!="0") { i++; }
    if(i<7){
        functions_[i].create_plot(expr,graph_.getPosition());
        func_expr_[i]=expr;
        return i;
    }
}

void Graph::delete_function(size_t i){
    functions_[i].clear(graph_.getPosition());
    func_expr_[i]="0";
}
