#include "case.hpp"

#include <iostream>
#include <random>



void Case::set_up_draw(std::vector<GLuint> listOfCaseTexture){

    // Création d'un générateur de nombres aléatoires à partir d'une source d'entropie
    std::random_device rd; 
    // Initialisation du moteur de génération de nombres aléatoires
    std::mt19937 gen(rd());
    // Définir la distribution, par exemple pour un entier entre 1 et 100
    std::uniform_int_distribution<> dis(10, 15);
    // Générer un nombre aléatoire
    int randomNumber = dis(gen);
    if(this->_type == typeCase::DECOR){
            _texture = listOfCaseTexture[randomNumber];
    }else if(this->_type == typeCase::PATH){
            _texture = listOfCaseTexture[0];
    }else if(this->_type == typeCase::PATH_T_B){
            _texture = listOfCaseTexture[2];
    }else if(this->_type == typeCase::PATH_R_L){
            _texture = listOfCaseTexture[3];
    }else if(this->_type == typeCase::PATH_B_L){
            _texture = listOfCaseTexture[4];
    }else if(this->_type == typeCase::PATH_B_R){
            _texture = listOfCaseTexture[5];
    }else if(this->_type == typeCase::PATH_T_L){
            _texture = listOfCaseTexture[6];
    }else if(this->_type == typeCase::PATH_T_R){
            _texture = listOfCaseTexture[7];
    }else if(this->_type == typeCase::START){
            _texture = listOfCaseTexture[8];
    }else if(this->_type == typeCase::END){
            _texture = listOfCaseTexture[9];
    }

}

void Case::draw_me(int nbrTiles){
        glPushMatrix();
            glTranslatef(pos.first, pos.second - 2./nbrTiles,0);
            glScalef(2./nbrTiles,-2./nbrTiles,1);
            draw_quad_with_texture(_texture);
        glPopMatrix();
}