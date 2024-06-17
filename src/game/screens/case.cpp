#include "case.hpp"


void Case::draw_me(int nbrTiles, std::vector<GLuint> listOfCaseTexture){
    if(this->_type == typeCase::DECOR){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[1]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[0]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH_T_B){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[2]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH_R_L){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[3]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH_B_L){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[4]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH_B_R){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[5]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH_T_L){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[6]);
        glPopMatrix();
    }else if(this->_type == typeCase::PATH_T_R){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[7]);
        glPopMatrix();
    }else if(this->_type == typeCase::START){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[8]);
        glPopMatrix();
    }else if(this->_type == typeCase::END){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(listOfCaseTexture[9]);
        glPopMatrix();
    }

}