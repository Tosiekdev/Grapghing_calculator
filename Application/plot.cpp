//
// Created by tosiek on 14.06.22.
//

#include "plot.h"

int Plot::count_=0;

Plot::Plot(){
    for(auto &i:lines1_){
        i.setPrimitiveType(sf::Lines);
        i.resize(2);
        i[0].color=colors[count_%7];
        i[1].color=colors[count_%7];
    }

    for(auto &i:lines10_){
        i.setPrimitiveType(sf::Lines);
        i.resize(2);
        i[0].color=colors[count_%7];
        i[1].color=colors[count_%7];
    }

    for(auto &i:lines100_){
        i.setPrimitiveType(sf::Lines);
        i.resize(2);
        i[0].color=colors[count_%7];
        i[1].color=colors[count_%7];
    }

    count_++;
}

void Plot::create_plot(const std::string &expr, sf::Vector2f position){
    function_.start(expr);
    calc_values(values1_,1,lines1_,position);
    calc_values(values10_,10,lines10_,position);
    calc_values(values100_,100,lines100_,position);
}

void Plot::draw(sf::RenderWindow &window, int scale){
    switch(scale){
        case 1:
            for(auto &i:lines1_) { window.draw(i); }
            break;
        case 10:
            for(auto &i:lines10_) { window.draw(i); }
            break;
        case 100:
            for(auto &i:lines100_) { window.draw(i); }
            break;
        default:
            for(auto &i:lines1_) { window.draw(i); }
    }
}

void Plot::calc_values(std::array<double,prc+1>&values,int scale,std::array<sf::VertexArray,prc>&lines,sf::Vector2f pos){
    double x=-scale;
    double delta=static_cast<double>(scale)/(0.5*prc);
    size_t i=0;
    while(x<=scale){
        try{
            values[i] = function_.calc_value(x);
        }
        catch(const az::OutOfDomain &e){
            values[i] = std::numeric_limits<double>::quiet_NaN();
        }
        i++;
        x+=delta;
    }

    for(size_t j=0; j < prc; j++){
        if(!std::isnan(values[j])){
            lines[j][0].position.x= pos.x + (float)j * 1000/prc;
            lines[j][0].position.y=(float)(pos.y + 500 - values[j] * 500.f / scale);
            if(!std::isnan(values1_[j + 1]) && abs(int((values[j+1]-values[j])*500.f/scale))<700){
                lines[j][1].position.x= pos.x + (float)(j + 1) * 1000/prc;
                lines[j][1].position.y=(float)(pos.y + 500 - values[j + 1] * 500.f / scale);
            }else{
                lines[j][1].position.x= pos.x + (float)j * 1000/prc;
                lines[j][1].position.y=(float)(pos.y + 500 - values[j] * 500.f / scale);
            }
        }
    }
}

double Plot::calc_value(double x){
    return function_.calc_value(x);
}

void Plot::clear(sf::Vector2f pos){
    for(auto &i:lines1_){
        i[0].position=pos+sf::Vector2f(0,500);
        i[1].position=pos+sf::Vector2f(0,500);
    }
    for(auto &i:lines10_){
        i[0].position=pos+sf::Vector2f(0,500);
        i[1].position=pos+sf::Vector2f(0,500);
    }
    for(auto &i:lines100_){
        i[0].position=pos+sf::Vector2f(0,500);
        i[1].position=pos+sf::Vector2f(0,500);
    }
}
