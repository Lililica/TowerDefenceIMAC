#include "button.hpp"
#include "../../App.hpp"


void Button::draw_me(){
    glPushMatrix();
        glTranslatef(posX, -posY, 0);
        glScalef(width,-height,1);
        draw_quad_with_texture(texture);
    glPopMatrix();
}


void App::update_all_myButton(){
    // std::cout << listOfButton[0].isPressed << std::endl;

}