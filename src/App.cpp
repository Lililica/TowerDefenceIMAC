#include "App.hpp"
#include "game/draws/draw.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>
#include <sstream>
#include <iostream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"


std::pair<double, double> App::screen_px_to_squareScreen_px(std::pair<double, double> pos){
    pos.first = (pos.first - (_width - _height)/2)*size - (_height -(_height*size))/2;
    pos.second = pos.second*size - (_height -(_height*size))/2;
    return pos;
}

std::pair<double, double> App::squareScreen_px_to_squareScreen_abs(std::pair<double, double> pos){
    pos.first = (pos.first*2)/(((_height - (_height -(_height*size))/2))*size - (_height -(_height*size))/2) - 1.f;
    pos.second =  -(pos.second*2)/(((_height - (_height -(_height*size))/2))*size - (_height -(_height*size))/2) + 1.f;
    return pos;
}


std::pair<double, double> App::squareScreen_abs_to_SquareScreen_tiles(std::pair<double, double> pos){
    pos.first = (int((pos.first + 1)*_numberOfTiles/2))*(2/float(_numberOfTiles)) - 1. + 2/float(_numberOfTiles);
    pos.second = -(_numberOfTiles - int((pos.second + 1)*_numberOfTiles/2) - 1)*(2/float(_numberOfTiles)) + 1. - 2/float(_numberOfTiles);
    return pos;
}



App::App() : _previousTime(0.0), _viewSize(2.0) {
   // load what needs to be loaded here (for example textures)

    img::Image test {img::load(make_absolute_path("images/level.png", true), 3, true)};

    img::Image playButton {img::load(make_absolute_path("images/playbutton.png", true), 3, true)};
    
    _texture = loadTexture(playButton);
    
    // _texture = loadTexture(test);
}


void App::setup() {
    // Set the clear color to a nice blue
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    setup_drawing();

    // Setup the text renderer with blending enabled and white text color
    TextRenderer.ResetFont();
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.EnableBlending(true);

    std::vector<int> listTypeCase {};
    for (size_t i = 0; i < 20*20; i++){listTypeCase.push_back(i);}
    myScreen.create_list_of_case(listTypeCase);

    for (auto &&tile : myScreen.listCase)
    {
        std::cout << tile.index << " : " << tile.pos.first << ',' <<   tile.pos.second << std::endl;
    }
    
    listOfButton.push_back(
        Button{typeButton::PLAY,std::pair<double,double>{-0.1, 0.1,}, std::pair<double,double>{0.2, 0.2}, false, _texture}
    );
}

void App::update() {

    const double currentTime { glfwGetTime() };
    const double elapsedTime { currentTime - _previousTime};
    _previousTime = currentTime;


    mouse_pos = screen_px_to_squareScreen_px(mouse_pos);

    pos_mouse_abs = squareScreen_px_to_squareScreen_abs(mouse_pos);
    
    pos_tile_mouse = squareScreen_abs_to_SquareScreen_tiles(pos_mouse_abs);
   
    // UwU 
    render();
}

void App::render() {
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glScalef(size, size, 1);
        draw_all_content();
    glPopMatrix();



    TextRenderer.Render();
}

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/) {
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/) {
    for(Button currentButton : listOfButton){
        std::cout << "mouseX : " <<pos_mouse_abs.first << " " << "mouseY : " <<pos_mouse_abs.second << std::endl;
        std::cout << "abscisse entre : [" << currentButton.pos.first << ", " << currentButton.pos.first + currentButton.size.first << "]" << std::endl;
        std::cout << "ordonné entre : [" << -currentButton.pos.second << ", " << -(currentButton.pos.second - currentButton.size.second) << "]" << std::endl;

        if(pos_mouse_abs.first > currentButton.pos.first && pos_mouse_abs.first < currentButton.pos.first + currentButton.size.first
        && pos_mouse_abs.second > -currentButton.pos.second && pos_mouse_abs.second < -(currentButton.pos.second - currentButton.size.second))
        {
            myScreen._state = screen_state::LEVEL;
        }
        
    }
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/) {
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/) {
}

void App::size_callback(int width, int height) {
    _width  = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio { _width / (float) _height };

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(aspectRatio > 1.0f) {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    } else {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}


