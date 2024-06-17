#include "App.hpp"
#include "game/draws/draw.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>
#include <sstream>
#include <iostream>
#include <vector>

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
    // std::cout << "First prev : " << pos.first << std::endl;
    // pos.first = (int((pos.first + 1)*_numberOfTiles/2))*(2/float(_numberOfTiles)) - 1. + 2/float(_numberOfTiles);
    pos.first = std::floor(pos.first * _numberOfTiles / 2.0) * (2.0 / _numberOfTiles);
    // pos.second = -(_numberOfTiles - int((pos.second + 1)*_numberOfTiles/2) - 1)*(2/float(_numberOfTiles)) + 1. - 2/float(_numberOfTiles);
    pos.second = std::floor(pos.second * _numberOfTiles / 2.0) * (2.0 / _numberOfTiles);
    return pos;
}




App::App() : _previousTime(0.0), _viewSize(2.0) {
   // load what needs to be loaded here (for example textures)

    img::Image test {img::load(make_absolute_path("images/level.png", true), 3, true)};    
    img::Image enemyImg {img::load(make_absolute_path("images/enemyTest.png", true), 3, true)};

    // Load background textures
    listOfBackgroundTextures.push_back({screen_state::MAIN_MENU,img::load(make_absolute_path("images/menu_background.png", true), 3, false)});
    listOfBackgroundTextures.push_back({screen_state::PAUSE_MENU,img::load(make_absolute_path("images/pause_background.png", true), 3, false)});
    listOfBackgroundTextures.push_back({screen_state::LEVEL,img::load(make_absolute_path("images/level_background.png", true), 3, false)});
    
    // img::Image playButton {img::load(make_absolute_path("images/playbutton.png", true), 3, true)};
    // _texture = loadTexture(playButton);
    
    _enemyTextureTest = loadTexture(enemyImg);
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

    // Création des cases
    double tileSize {2/float(_numberOfTiles)};
    std::vector<int> listTypeCase {};
    for (size_t i = 0; i < 20*20; i++){listTypeCase.push_back(i);}
    myScreen.create_list_of_case(listTypeCase);

    for (auto &&tile : myScreen.listCase){
        std::cout << tile.index << " : " << tile.pos.first << ',' <<   tile.pos.second << std::endl;
    }
    
    // Création des boutons
    listOfButton.push_back(Button{typeButton::BEGIN,std::pair<double,double>{-0.2, 0.3,}, std::pair<double,double>{0.4, 0.2}, false});
    listOfButton.push_back(Button{typeButton::CREDIT,std::pair<double,double>{-0.2, 0.0,}, std::pair<double,double>{0.4, 0.2}, false});
    listOfButton.push_back(Button{typeButton::QUIT,std::pair<double,double>{-0.2, -0.3,}, std::pair<double,double>{0.4, 0.2}, false});
    listOfButton.push_back(Button{typeButton::PAUSE,std::pair<double,double>{-1.4, 0.1,}, std::pair<double,double>{0.4, 0.2}, false});
    listOfButton.push_back(Button{typeButton::PLAY,std::pair<double,double>{-0.1, 0.1,}, std::pair<double,double>{0.2, 0.2}, false});
    for (auto &&button : listOfButton) {button.set_stats_from_type();}

    // Création des tours
    listOfTower.push_back(Tower{typeTower::TYPE1,int{1}, std::pair<double,double>{-1, 0.5,}});
    listOfTower.push_back(Tower{typeTower::TYPE2,int{2}, std::pair<double,double>{0.5, -0.2,}});
    listOfTower.push_back(Tower{typeTower::TYPE3,int{3}, std::pair<double,double>{0.8, 0.8,}});
    listOfTower.push_back(Tower{typeTower::TYPE4,int{4}, std::pair<double,double>{-0.1, -0.8,}});
    for (auto &&tower : listOfTower) {tower.set_stats_from_type();tower.set_range_box(tileSize);}
    
    // Création des ennemis
    listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, _enemyTextureTest});

}

void App::update() {

    const double currentTime { glfwGetTime() };
    const double elapsedTime { currentTime - _previousTime};
    _previousTime = currentTime;


    mouse_pos = screen_px_to_squareScreen_px(mouse_pos);

    pos_mouse_abs = squareScreen_px_to_squareScreen_abs(mouse_pos);
    
    pos_tile_mouse = squareScreen_abs_to_SquareScreen_tiles(pos_mouse_abs);

    if(myScreen._state == screen_state::LEVEL){
        if(listOfEnemy.size() != 0) listOfEnemy[0].is_walking();
    }
    
    if(listOfEnemy.size() != 0) {
        for (auto &&tower : listOfTower){
            if(collision_box_box(listOfEnemy[0].pos, {listOfEnemy[0].width, listOfEnemy[0].height}, tower.rangeBox.first, tower.rangeBox.second)) {
                listOfEnemy[0].lifePoint -= 2;
            }
        }
        for (auto &&enemy : listOfEnemy){
            if(enemy.lifePoint <= 0) {
                std::cout << "Enemy died" << std::endl;
                //quand un enemy meurt
            }
        }
        removeDeadEnemies();
    }
    
    
    
   
    // UwU 
    render();
}

void App::render() {
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.5,0.5,0.5,1);

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
        // std::cout << "mouseX : " <<pos_mouse_abs.first << " " << "mouseY : " <<pos_mouse_abs.second << std::endl;
        // std::cout << "abscisse entre : [" << currentButton.pos.first << ", " << currentButton.pos.first + currentButton.size.first << "]" << std::endl;
        // std::cout << "ordonné entre : [" << -currentButton.pos.second << ", " << -(currentButton.pos.second - currentButton.size.second) << "]" << std::endl;

        if(collision_pos_box(pos_mouse_abs, currentButton.pos, currentButton.size)) {
            switch (currentButton._type){
            case BEGIN:
            case PLAY:
                myScreen._state = screen_state::LEVEL;
                break;
            case PAUSE:
                // A changer
                myScreen._state = screen_state::PAUSE_MENU;
                break;
            case RESTART:
                // A changer
                myScreen._state = screen_state::MAIN_MENU;
                break;
            case QUIT:
                // Close window
                myScreen._state = screen_state::MAIN_MENU;
                break;
            case CREDIT:
                // A changer
                myScreen._state = screen_state::MAIN_MENU;
                break;
            default:
                break;
            }
        }
        // if(pos_mouse_abs.first > currentButton.pos.first && pos_mouse_abs.first < currentButton.pos.first + currentButton.size.first
        // && pos_mouse_abs.second > -currentButton.pos.second && pos_mouse_abs.second < -(currentButton.pos.second - currentButton.size.second))
        // {
        //     myScreen._state = screen_state::LEVEL;
        // }
        
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




void App::removeDeadEnemies() {
    listOfEnemy.erase(
        std::remove_if(listOfEnemy.begin(), listOfEnemy.end(), [](const auto& enemy) {
            return enemy.lifePoint <= 0;
        }),
        listOfEnemy.end()
    );
}