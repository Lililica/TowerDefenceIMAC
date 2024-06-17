
#include "../../App.hpp"
#include "shape.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"
#include "game/utilitaires/outil.hpp"
#include "game/entities/entity.hpp"
#include <game/draws/draw.hpp>
#include <iostream>

void setup_drawing(){
    return;
}

void App::draw_background(screen_state const& Screen) {
    std::pair<double, double> globalCoords {squareScreen_px_to_squareScreen_abs(screen_px_to_squareScreen_px({_width, _height}))};
    double width {abs(globalCoords.first*2)};
    double height {abs(globalCoords.second*2)};

    //-------------------ratio image 16/9

    auto menuBg {std::find_if(listOfBackgroundTextures.begin(), listOfBackgroundTextures.end(), [Screen](const auto& img) {
                    return img.first == Screen;
                })};
    if (menuBg != listOfBackgroundTextures.end()) {
        
        glPushMatrix();
            if(height*16/width > 9) { //si plus haut que l'image doit dépasser horizontalement
                width = height*16/9;
                glTranslatef(-width/2, height/2, 0);
                glScalef(width, height, 1.0f);
            } else { //sinon plus large que l'image doit dépasser verticalement
                height = width*9/16;
                glTranslatef(-width/2, height/2, 0);
                glScalef(width, height, 1.0f);
            }
            draw_quad_with_texture(loadTexture(menuBg->second));
        glPopMatrix();

    } else {
        std::cout << Screen << " image not found!" << std::endl;
    }
}




void App::draw_all_content(){
    double tileSize {2/float(_numberOfTiles)};
    std::string print_screen_state {};

    // ---------------------------------------------------
    // MAIN MENU
    // ---------------------------------------------------
    if(myScreen._state == screen_state::MAIN_MENU){
        print_screen_state = "MAIN MENU";

        draw_background(screen_state::MAIN_MENU);

        for(Button button : listOfButton){
            if( button._type == typeButton::BEGIN || 
                button._type == typeButton::CREDIT ||
                button._type == typeButton::QUIT
            )button.draw_me();
        }
    }

    // ---------------------------------------------------
    // PAUSE MENU
    // ---------------------------------------------------
    if(myScreen._state == screen_state::PAUSE_MENU){
        print_screen_state = "PAUSE MENU";

        draw_background(screen_state::PAUSE_MENU);

        for(Button button : listOfButton){
            if( button._type == typeButton::PLAY || 
                button._type == typeButton::RESTART ||
                button._type == typeButton::QUIT
            )button.draw_me();
        }
    }

    // ---------------------------------------------------
    // LEVELS
    // ---------------------------------------------------
    if(myScreen._state == screen_state::LEVEL){
        print_screen_state = "LEVEL";

        draw_background(screen_state::LEVEL);

        // for(Case myCase : myScreen.listCase){
        //     myCase.draw_me(_numberOfTiles, listOfCaseTexture);
        // }

        // glColor3f(1.0f, 0.0f, 0.0f);
        // drawRect(-1,-1,2,2);

        for(Tower tower : listOfTower){
            tower.draw_range_box();
        }
        for(Tower tower : listOfTower){
            tower.draw_me(tileSize);
        }

        if(listOfEnemy.size() != 0) {
            for(Enemy enemy : listOfEnemy){
                enemy.draw_me();
                enemy.draw_my_lp();
            }
        }

        for(Button button : listOfButton){
            if( button._type == typeButton::PAUSE
            )button.draw_me();
        }
        
        // ---------------------------------------------------
        // Draw debug
        // ---------------------------------------------------

            std::string debug_tiles_pos_text {};
            std::stringstream stream {};
            stream << std::fixed << "Tile MouseX: " << std::setprecision(2) << pos_tile_mouse.first << " et Tile MouseY: " << std::setprecision(2) << pos_tile_mouse.second;
            debug_tiles_pos_text = stream.str();
            TextRenderer.Label(debug_tiles_pos_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

            // if(pos_tile_mouse.first > -1. && pos_tile_mouse.first <= 1.01 && pos_tile_mouse.second >= -1.01 && pos_tile_mouse.second < 1.){
            //     glPushMatrix();
            //         glColor3f(0.0f, 0.0f, 1.0f);
            //         drawRect(pos_tile_mouse.first, pos_tile_mouse.second, -tileSize, tileSize);
            //     glPopMatrix();
            // }
            if (collision_pos_box({pos_tile_mouse.first,pos_tile_mouse.second},{-1,-1},{1.999,1.999})) {
                glPushMatrix();
                    glColor3f(0.0f, 0.0f, 1.0f);
                    drawRect(pos_tile_mouse.first, pos_tile_mouse.second, tileSize, tileSize);
                glPopMatrix();
            }

        // ---------------------------------------------------
        // Draw Lines
        // ---------------------------------------------------

            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINES);
            for(int i{0}; i < _numberOfTiles + 1; i++){
                glVertex2f((2*i/float(_numberOfTiles)-1.), -1.f);
                glVertex2f((2*i/float(_numberOfTiles)-1.), 1.f);
                glVertex2f(-1.f, (2*i/float(_numberOfTiles)-1.));
                glVertex2f(1.f, (2*i/float(_numberOfTiles)-1.));
            }
            glEnd();
    }

    TextRenderer.Label(print_screen_state.c_str(), 100, 100, SimpleText::CENTER);

}