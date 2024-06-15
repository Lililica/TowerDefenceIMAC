#include "tower.hpp"
#include <img/img.hpp>

#include <utility>
#include <sstream>
#include <iostream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"
#include "../draws/shape.hpp"
#include "../utilitaires/outil.hpp"

img::Image defaultTower {img::load(make_absolute_path("images/towers/towerdefault.png", true), 3, true)};
img::Image type1Tower {img::load(make_absolute_path("images/towers/tower1.png", true), 3, true)};
img::Image type2Tower {img::load(make_absolute_path("images/towers/tower2.png", true), 3, true)};
img::Image type3Tower {img::load(make_absolute_path("images/towers/tower3.png", true), 3, true)};
img::Image type4Tower {img::load(make_absolute_path("images/towers/tower4.png", true), 3, true)};

void Tower::set_stats_from_type() {
    switch (_type) {
        case TYPE1:
            _texture = loadTexture(type1Tower);
            power = 1;
            range = 1;
            lifePoint = 5;
            attackSpeed = 1;
            break;
        case TYPE2:
            _texture = loadTexture(type2Tower);
            power = 2;
            range = 2;
            lifePoint = 5;
            attackSpeed = 2;
            break;
        case TYPE3:
            _texture = loadTexture(type3Tower);
            power = 3;
            range = 3;
            lifePoint = 5;
            attackSpeed = 3;
            break;
        case TYPE4:
            _texture = loadTexture(type4Tower);
            power = 4;
            range = 4;
            lifePoint = 5;
            attackSpeed = 4;
            break;
        default:
            _texture = loadTexture(defaultTower);
            power = 1;
            range = 1;
            lifePoint = 1;
            attackSpeed = 1;
    }
}


void Tower::draw_me(){
    glPushMatrix();
        glTranslatef(pos.first, pos.second, 0);
        // glScalef(0.1,-0.1,1);
        draw_quad_with_texture(_texture);
    glPopMatrix();
}
void Tower::draw_range(){
    glPushMatrix();
        glColor3f(1.0,1.0,0.5);

        // glTranslatef(pos.first, -pos.second, 0);
        // glScalef(0.1*range,0.1*range,1);

        double rangeSideSize {range*0.1};
        double rectLeft = pos.first-rangeSideSize;
        double rectRight = pos.first+rangeSideSize;
        double rectBottom = pos.second-rangeSideSize;
        double rectTop = pos.second+rangeSideSize;

        if (rectLeft < -0.9) rectLeft = -0.9;
        if (rectRight > 1) rectRight = 1;
        if (rectBottom < -1) rectBottom = -1;
        if (rectTop > 0.9) rectTop = 0.9;

        drawRect(
            rectLeft, rectBottom,
            0.1,0.1
        );
        // for (int i = 0; i < range*2+1; i++){
        //     for (int j = 0; j < range*2+1; j++){
        //         double x {pos.first-(range*0.1)+(i*0.1)};
        //         double y {pos.second-(range*0.1+0.1)+(j*0.1)};
        //         double s {0.1};
        //         if(collision_box_box({x,y}, {s,s}, {-0.9,-0.9}, {1.9,1.9})) {drawRect(x, y, s, s);}
        //     }
        // }
        
    glPopMatrix();
}
// void Tower::draw_range() {
//     // Taille d'une case de la grille
//     const double cellSize = 0.1;

//     // Calcul de la position ajustée pour centrer sur une case de la grille
//     double centerX = pos.first;
//     double centerY = pos.second;

//     // Calcul du demi-taille du rectangle en termes de nombre de cases
//     double halfRange = range * cellSize;
    
//     // Coordonnées du rectangle
//     double rectLeft = centerX - halfRange;
//     double rectBottom = centerY - halfRange;
//     double rectRight = centerX + halfRange + cellSize;
//     double rectTop = centerY + halfRange + cellSize;

//     // Vérification des limites du rectangle par rapport au canva global
//     double globalLeft = -0.9;
//     double globalRight = 1.0;
//     double globalBottom = -0.9;
//     double globalTop = 1.0;

//     if (rectLeft < globalLeft) rectLeft = globalLeft;
//     if (rectRight > globalRight) rectRight = globalRight;
//     if (rectBottom < globalBottom) rectBottom = globalBottom;
//     if (rectTop > globalTop) rectTop = globalTop;

//     double rectWidth = rectRight - rectLeft;
//     double rectHeight = rectTop - rectBottom;

//     glPushMatrix();
//         glColor3f(1.0, 0.5, 0.75);
//         drawRect(rectLeft, rectBottom, rectWidth, rectHeight);
//     glPopMatrix();
// }










