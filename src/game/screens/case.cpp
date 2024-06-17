#include "case.hpp"


void Case::draw_me(int nbrTiles, std::vector<GLuint> listOfCaseTexture){
    if(this->_type == typeCase::DECOR){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[0]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[1]);
        glPopMatrix();
    }

}