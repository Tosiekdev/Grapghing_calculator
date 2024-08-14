# Grapghing_calculator
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) <br />
Graphing calculator propably

## Instalation
Only thing you need to do is copy the contents of ```imconfig-SFML.h``` to your ```imconfig.h``` file. (to be able to cast ```ImVec2``` to ```sf::Vector2f``` and vice versa). It's also an option that you are not using Linux, then you have to link OpenGL in a diffrent way (as default flag -lGL is added in ```CmakeList.txt```). 

## Font
If you want to use font, copy `OpenSans-VariableFont_wdth,wght.ttf` to your
build folder. In case of any changes in path to font
please refer to `fontPath` in `Application/app.h`.
