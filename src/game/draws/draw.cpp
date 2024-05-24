
#include "../../App.hpp"
#include "shape.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"
#include <iostream>

void setup_drawing(){
    return;
}

void App::draw_all_content(){
    std::string print_screen_state {};

    if(myScreen._state == state::MAIN_MENU){
        print_screen_state = "MAIN MENU";
    }

    if(myScreen._state == state::LEVEL){
        print_screen_state = "LEVEL";

        glColor3f(1.0f, 0.0f, 0.0f);
        drawRect(-1,-1,2,2);





        // Draw debug

        std::string debug_tiles_pos_text {};
        std::stringstream stream {};
        stream << std::fixed << "Tile MouseX: " << std::setprecision(2) << pos_tile_mouse.first << " et Tile MouseY: " << std::setprecision(2) << pos_tile_mouse.second;
        debug_tiles_pos_text = stream.str();
        TextRenderer.Label(debug_tiles_pos_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

        if(pos_tile_mouse.first > -1. && pos_tile_mouse.first <= 1.01 && pos_tile_mouse.second >= -1.01 && pos_tile_mouse.second < 1.){

            glPushMatrix();
                glColor3f(0.0f, 0.0f, 1.0f);
                drawRect(pos_tile_mouse.first, pos_tile_mouse.second, -2/float(_numberOfTiles), 2/float(_numberOfTiles));
            glPopMatrix();
        }


        // Draw Lines

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