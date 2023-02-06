//
// Created by tosiek on 16.06.22.
//

#include "manual.h"

void Manual::handle_events(sf::RenderWindow &window, Scene &scene) {
    while(window.pollEvent(e_)){
        ImGui::SFML::ProcessEvent(window, e_);
        switch(e_.type){
            case sf::Event::KeyPressed:
                if(e_.key.code == sf::Keyboard::Escape) { scene=MENU; }
                break;
            default:
                ;
        }
    }
}

void Manual::do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    ImGui::SFML::Update(window, deltaClock.restart());

    background(window, scene);
    title(window, scene);
    returning_button(window, deltaClock, scene);
    help(window, scene);
}

void Manual::display(sf::RenderWindow &window){
    window.clear(sf::Color::White);

    ImGui::SFML::Render(window);

    window.display();
}

void Manual::help(sf::RenderWindow &window, Scene &scene) {
    //Getting window's size for scaling
    auto size = window.getSize();
    auto x = static_cast<float>(size.x);
    auto y = static_cast<float>(size.y);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(x/3.f,2*y/13.5f));
    ImGui::SetNextWindowSize(ImVec2(x/3.f,y-y/13.5f));

    //Color theme
    ImGui::StyleColorsLight();

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
    ImGui::Begin("Function tools", nullptr, flags);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::Text("This is graphing calculator(probably).");
    ImGui::Text("It offers various types of functions such as:");
    ImGui::BulletText("trigonometric functions");
    ImGui::BulletText("cyclometric functions,");
    ImGui::BulletText("exponetial functions,");
    ImGui::BulletText("logarithmic functions,");
    ImGui::BulletText("polynomials.");
    ImGui::Text("To make everything looks and works fine remember:");
    ImGui::BulletText("two arguments symbols (*,^,/) like to work other than \n BODMAS tells so to be sure use brackets,");
    ImGui::BulletText("^ means power, * means multiplication (remember to always \n use it), / means division,");
    ImGui::BulletText("2x won't work,");
    ImGui::BulletText("pi in function is treated as 3.1415926563589793,");
    ImGui::BulletText("e is treated as Euler's number (i don't remember digits),");
    ImGui::BulletText("this two above doesn't work as an argument.");
    ImGui::Text("Have a good time playing with it, don't broke everything.");
    ImGui::Text("Bad usage can cause freeze.");
    ImGui::PopFont();
    ImGui::End();
}
