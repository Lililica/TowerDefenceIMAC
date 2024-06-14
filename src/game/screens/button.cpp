#include "button.hpp"

void Button::draw_me(){
    glPushMatrix();
        glTranslatef(pos.first, -pos.second, 0);
        glScalef(size.first,-size.second,1);
        draw_quad_with_texture(_texture);
    glPopMatrix();
}


