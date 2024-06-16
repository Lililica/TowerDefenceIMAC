#include "entity.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include "../draws/shape.hpp"

// --------------------------------------------------------------
// Enemy
// --------------------------------------------------------------

void Enemy::is_walking(){

    Case case1 {listOfNodes[itTKT]};       
    Case case2 {listOfNodes[itTKT + 1]};


    if(case1.pos.first == case2.pos.first && case1.pos.second < case2.pos.second){
        direction = Direction::BOTTOM;
    }else if(case1.pos.first == case2.pos.first && case1.pos.second > case2.pos.second){
        direction = Direction::TOP;
    }else if(case1.pos.second == case2.pos.second && case1.pos.first < case2.pos.first){
        direction = Direction::RIGHT;
    }else if(case1.pos.second == case2.pos.second && case1.pos.first < case2.pos.first){
        direction = Direction::LEFT;
    }

    if(pos.first >= case2.pos.first && pos.first <= case2.pos.first + 1./nbrTileSide &&
        pos.second >= -case2.pos.second && pos.second <= -(case2.pos.second - 1./nbrTileSide)){   //A MODIFIER
        itTKT = (itTKT+1)%3;
    }else{
        if(direction == Direction::RIGHT){
            pos.first += speed;
        }else if(direction == Direction::BOTTOM){
            pos.second -= speed;
        }else if(direction == Direction::LEFT){
            pos.first -= speed;
        }else{
            pos.second += speed;
        }   
    }
}

void Enemy::draw_me(){
    glPushMatrix();
        glTranslatef(pos.first, pos.second - height,0);
        glScalef(width,-height,1);
        draw_quad_with_texture(texture);
    glPopMatrix();
}

// --------------------------------------------------------------
// TOWER
// --------------------------------------------------------------

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


void Tower::draw_me(double tileSize){
    glPushMatrix();
        glTranslatef(pos.first, pos.second, 0);
        glScalef(tileSize,-tileSize,1);
        draw_quad_with_texture(_texture);
    glPopMatrix();
}
void Tower::set_range_box(double tileSize) {
    double rangeSideSize {range*tileSize};
    double rectLeft = pos.first-rangeSideSize;
    double rectRight = pos.first+rangeSideSize;
    double rectBottom = pos.second-rangeSideSize;
    double rectTop = pos.second+rangeSideSize;

    if (rectLeft < -1) rectLeft = -1;
    if (rectRight > 0.9) rectRight = 0.9;
    if (rectBottom < -1) rectBottom = -1;
    if (rectTop > 0.9) rectTop = 0.9;

    rangeBox = {{rectLeft, rectBottom}, {rectRight - rectLeft + tileSize, rectTop - rectBottom + tileSize}};
}
void Tower::draw_range_box(){
    glPushMatrix();
        glColor3f(1.0,1.0,0.5);
        // glTranslatef(pos.first, -pos.second, 0);
        // glScalef(0.1*range,0.1*range,1);

        drawRect(
            rangeBox.first.first, rangeBox.first.second,
            rangeBox.second.first,
            rangeBox.second.second
        );
    glPopMatrix();
}

// void Tower::remove_bullet(Bullet bullet){
//     std::remove(listOfBullet.begin(), listOfBullet.end(), bullet);
// }