#include "entity.hpp"



void Ennemy::draw_me(){
    glPushMatrix();
        glTranslatef(pos.first, -pos.second, 0);
        glScalef(taille.first,-taille.second,1);
        draw_quad_with_texture(texture);      
    glPopMatrix();
}