//
// Created by tosiek on 14.06.22.
//

#include "calculator.h"

Calculator::Calculator(){
    is_focused=false;

    x1_.create_button(sf::Vector2f(1010,85),sf::Vector2f(0.2f,0.3f),"1x");
    x10_.create_button(sf::Vector2f(1010,135),sf::Vector2f(0.2f,0.3f),"10x");
    x100_.create_button(sf::Vector2f(1010,185),sf::Vector2f(0.2f,0.3f),"100x");

    remove_func_.create_button(sf::Vector2f(1300,475),sf::Vector2f(0.3,0.3),"Remove");
    calc_.create_button(sf::Vector2f(1650,475),sf::Vector2f(0.3,0.3),"Calculate");

    graph.set_position(sf::Vector2f(0,80));

    for(int i=0; i<7; i++){
        func_colors_[i].setSize(sf::Vector2f(30,30));
        func_colors_[i].setOutlineThickness(5);
        func_colors_[i].setOutlineColor(sf::Color::Black);
        func_colors_[i].setFillColor(colors[i]);
        func_colors_[i].setPosition(sf::Vector2f(1010, 630+(float)i*50));

        func_caps_[i].loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
        func_caps_[i].setOrigin(sf::Vector2f(0,0));
        func_caps_[i].setString(graph[i]);
        func_caps_[i].setPosition(sf::Vector2f(1055, 630+(float)i*50));
        func_caps_[i].setFillColor(sf::Color::Black);
        func_caps_[i].setCharacterSize(25);
    }

    textbox_.create_textbox(sf::Vector2f(1300,85),sf::Vector2f(1,1));
    select_func_.create_textbox(sf::Vector2f(1550,300),sf::Vector2f(0.5,0.7));
    argument_.create_textbox(sf::Vector2f(1550, 375), sf::Vector2f(0.5, 0.7));

    selected_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    selected_.setCharacterSize(30);
    selected_.setFillColor(sf::Color::Black);
    selected_.setString("Selected function:");
    selected_.setOrigin(sf::Vector2f(0,0));
    selected_.setPosition(sf::Vector2f(1300,300));

    f_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    f_.setCharacterSize(50);
    f_.setFillColor(sf::Color::Black);
    f_.setString("f(x):");
    f_.setOrigin(sf::Vector2f(0,0));
    f_.setPosition(sf::Vector2f(1150,85));

    calc_for_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    calc_for_.setCharacterSize(30);
    calc_for_.setFillColor(sf::Color::Black);
    calc_for_.setString("Argument:");
    calc_for_.setOrigin(sf::Vector2f(0, 0));
    calc_for_.setPosition(sf::Vector2f(1300, 375));

    f_calculated_.loadFromFile("Fonts/KdamThmorPro-Regular.ttf");
    f_calculated_.setCharacterSize(30);
    f_calculated_.setFillColor(sf::Color::Black);
    f_calculated_.setString("f(x)=?");
    f_calculated_.setOrigin(sf::Vector2f(0, 0));
    f_calculated_.setPosition(sf::Vector2f(1300, 575));
}

void Calculator::handle_events(sf::RenderWindow &window, Scene &scene) {
    while(window.pollEvent(e_)){
        ImGui::SFML::ProcessEvent(window, e_);
        switch (e_.type){
            case sf::Event::KeyPressed:
                if(e_.key.code == sf::Keyboard::Escape) { scene=MENU; }
                if(e_.key.code == sf::Keyboard::Enter){
                    if(textbox_.is_focused()){
                        auto pos = graph.create_plot(textbox_.get_content());
                        if(pos < 7){
                            func_caps_[pos].setString(graph[pos]);
                            func_caps_[pos].setOrigin(sf::Vector2f(0, 0));
                        }
                        textbox_.clear();
                        textbox_.focus(false);
                    }
                }
                break;
            case sf::Event::TextEntered:
                if(textbox_.is_focused()) {
                    if (e_.text.unicode!=8) {
                        char a=static_cast<char>(e_.text.unicode);
                        textbox_.update(a);
                    }
                    else{
                        textbox_.erase();
                    }
                }
                if(select_func_.is_focused()){
                    if (e_.text.unicode!=8) {
                        char a=static_cast<char>(e_.text.unicode);
                        select_func_.update(a);
                    }
                    else{
                        select_func_.erase();
                    }
                }
                if(argument_.is_focused()){
                    if (e_.text.unicode!=8) {
                        char a=static_cast<char>(e_.text.unicode);
                        argument_.update(a);
                    }
                    else{
                        argument_.erase();
                    }
                }
                break;
            default:
                ;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            auto mouse=sf::Mouse::getPosition(window);

            if(x1_.is_focused(mouse,cursor_,window)){
                graph.set_scale(1);
                not_focused();
            }
            if(x10_.is_focused(mouse,cursor_,window)){
                graph.set_scale(10);
                not_focused();
            }
            if(x100_.is_focused(mouse,cursor_,window)){
                graph.set_scale(100);
                not_focused();
            }
            if(remove_func_.is_focused(mouse,cursor_,window)){
                try{
                    size_t i=std::stoull(select_func_.get_content());
                    if(i<7){
                        graph.delete_function(i);
                        func_caps_[i].setString("0");
                    }
                }
                catch(std::invalid_argument &e){

                }
                not_focused();
            }
            if(calc_.is_focused(mouse,cursor_,window)){
                try{
                    size_t i=std::stoull(select_func_.get_content());
                    if(i<7){
                        try{
                            double x=std::stod(argument_.get_content());
                            f_calculated_.setString("f(x)="+std::to_string(graph.calc_value(i,x)));
                            f_calculated_.setOrigin(sf::Vector2f(0,0));
                        }
                        catch(std::invalid_argument &e){

                        }
                    }
                }
                catch(std::invalid_argument &e){

                }
                not_focused();
            }

            if(textbox_.mouse_above(mouse,cursor_,window)){
                textbox_.focus(true);
                select_func_.focus(false);
                argument_.focus(false);
            }
            if(select_func_.mouse_above(mouse,cursor_,window)){
                select_func_.focus(true);
                textbox_.focus(false);
                argument_.focus(false);
            }
            if(argument_.mouse_above(mouse,cursor_,window)){
                argument_.focus(true);
                textbox_.focus(false);
                select_func_.focus(false);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(textbox_.is_focused()) { textbox_.move_indicator(-1); }
            if(select_func_.is_focused()) { select_func_.move_indicator(-1); }
            if(argument_.is_focused()) { argument_.move_indicator(-1); }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(textbox_.is_focused()) { textbox_.move_indicator(1); }
            if(select_func_.is_focused()) { select_func_.move_indicator(1); }
            if(argument_.is_focused()) { argument_.move_indicator(1); }
        }
    }
}

void Calculator::do_stuff(sf::RenderWindow &window, sf::Clock &deltaClock, Scene &scene) {
    ImGui::SFML::Update(window, deltaClock.restart());
    auto mouse=sf::Mouse::getPosition();
    if(!is_focused) { is_focused=x1_.is_focused(mouse,cursor_,window); }
    if(!is_focused) { is_focused=x10_.is_focused(mouse,cursor_,window); }
    if(!is_focused) { is_focused=x100_.is_focused(mouse,cursor_,window); }
    if(!is_focused) { is_focused=remove_func_.is_focused(mouse,cursor_,window); }
    if(!is_focused) { is_focused=calc_.is_focused(mouse,cursor_,window); }
    if(!is_focused) { is_focused=textbox_.mouse_above(mouse,cursor_,window); }
    if(!is_focused) { is_focused=select_func_.mouse_above(mouse,cursor_,window); }
    if(!is_focused) { is_focused=argument_.mouse_above(mouse,cursor_,window); }


    title(window, scene);
    returning_button(window, deltaClock, scene);
    function_input(window, scene);
    _tools.show(window, scene);

    if(!is_focused){
        cursor_.loadFromSystem(sf::Cursor::Arrow);
        window.setMouseCursor(cursor_);
    }
}

void Calculator::display(sf::RenderWindow &window){
    window.clear(sf::Color::White);

    graph.draw(window);

    window.draw(remove_func_.getSprite());
    window.draw(remove_func_.getCaption());

    window.draw(f_calculated_.getText());

    window.draw(calc_.getSprite());
    window.draw(calc_.getCaption());

    window.draw(x1_.getSprite());
    window.draw(x1_.getCaption());
    window.draw(x10_.getSprite());
    window.draw(x10_.getCaption());
    window.draw(x100_.getSprite());
    window.draw(x100_.getCaption());

    for(auto &i:func_colors_) { window.draw(i); }
    for(auto &i:func_caps_) { window.draw(i.getText()); }

    textbox_.draw(window);
    select_func_.draw(window);
    argument_.draw(window);

    window.draw(f_.getText());
    window.draw(selected_.getText());
    window.draw(calc_for_.getText());

    ImGui::SFML::Render(window);

    window.display();
}

void Calculator::not_focused(){
    select_func_.focus(false);
    textbox_.focus(false);
    argument_.focus(false);
}

void Calculator::function_input(sf::RenderWindow &window, Scene &scene) {
    char row[20];
    //Getting window's size for scaling
    auto size = window.getSize();
    auto x = static_cast<float>(size.x);
    auto y = static_cast<float>(size.y);

    ImVec2 buttonSize = ImVec2(x/12.f,y/18.f);

    // Proper positioning
    ImGui::SetNextWindowPos(ImVec2(x/1.5f,100));
    ImGui::SetNextWindowSize(ImVec2(x/10.f,y/10.f));

    //Rounded edges
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

    int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
    ImGui::Begin("Function input", nullptr, flags);

    //Color theme
    ImGui::StyleColorsLight();

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::InputText("Function", row,20);
    ImGui::PopFont();
    ImGui::End();
    ImGui::PopStyleVar();
}
