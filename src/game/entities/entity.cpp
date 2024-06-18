#include "entity.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include "../draws/shape.hpp"

#include <math.h>
#define _USE_MATH_DEFINES
# define M_PI           3.14159265358979323846

// --------------------------------------------------------------
// Enemy
// --------------------------------------------------------------

void Enemy::is_walking(){
        
    if(itTKT < listOfNodes.size()-1){
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

        // std::cout << pos.first << "entre : [" << case2.pos.first << ", " << case2.pos.first + 2./nbrTileSide << std::endl;
        // std::cout << pos.second << "entre : [" << case2.pos.second << ", " << (case2.pos.second + 2./nbrTileSide) << std::endl;
    
        if(pos.first >= case2.pos.first && pos.first <= case2.pos.first + 2./nbrTileSide &&
            pos.second >= case2.pos.second - 2./nbrTileSide && pos.second <= case2.pos.second){   //A MODIFIER
            itTKT = itTKT+1;
            // std::cout << "J'y suis !" << std::endl;
        }else if(pos.first < 1.5 && pos.second < 1.5){
            if(direction == Direction::RIGHT){
                pos.first += speed;
            }else if(direction == Direction::BOTTOM){
                pos.second += speed;
            }else if(direction == Direction::LEFT){
                pos.first -= speed;
            }else{
                pos.second -= speed;
            }   
        }
    }
}

void Enemy::draw_my_lp(){
    glPushMatrix();
        glColor3f(0,1,0);
        drawRect(pos.first - 0.01, pos.second + 0.005, width + 0.02, 0.01 );
        glColor3f(1,0,0);
        drawRect(pos.first + width + 0.01, pos.second + 0.005 + 0.01, -(width + 0.02)*(float(initLP - lifePoint)/initLP), -0.01);
    glPopMatrix();
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

// Load tower textures
img::Image defaultTower {img::load(make_absolute_path("images/towers/towerdefault.png", true), 3, true)};
img::Image type1Tower {img::load(make_absolute_path("images/towers/tower1.png", true), 3, true)};
img::Image type2Tower {img::load(make_absolute_path("images/towers/tower2.png", true), 3, true)};
img::Image type3Tower {img::load(make_absolute_path("images/towers/tower3.png", true), 3, true)};
img::Image type4Tower {img::load(make_absolute_path("images/towers/tower4.png", true), 3, true)};

img::Image defaultBullet {img::load(make_absolute_path("images/towers/bullettest.png", true), 3, true)};

void Tower::set_stats_from_type() {
    switch (_type) {
        case TYPE1:
            _texture = loadTexture(type1Tower);
            _bulletTexture = loadTexture(defaultBullet);
            power = 2;
            range = 1;
            lifePoint = 5;
            attackSpeed = 0.1;
            break;
        case TYPE2:
            _texture = loadTexture(type2Tower);
            _bulletTexture = loadTexture(defaultBullet);
            power = 4;
            range = 2;
            lifePoint = 5;
            attackSpeed = 0.2;
            break;
        case TYPE3:
            _texture = loadTexture(type3Tower);
            _bulletTexture = loadTexture(defaultBullet);
            power = 6;
            range = 3;
            lifePoint = 5;
            attackSpeed = 0.3;
            break;
        case TYPE4:
            _texture = loadTexture(type4Tower);
            _bulletTexture = loadTexture(defaultBullet);
            power = 8;
            range = 4;
            lifePoint = 5;
            attackSpeed = 0.4;
            break;
        default:
            _texture = loadTexture(defaultTower);
            _bulletTexture = loadTexture(defaultBullet);
            power = 1;
            range = 1;
            lifePoint = 1;
            attackSpeed = 0.1;
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
        drawRect(
            rangeBox.first.first, rangeBox.first.second,
            rangeBox.second.first,
            rangeBox.second.second
        );
    glPopMatrix();
}

// void Tower::lance_bullet(int nbrTiles){
    // std::pair<double,double> posBtwEnemyTower {abs(pos.first)};
// }

void Tower::remove_bullet(const Bullet& bullet) {
    listOfBullet.erase(
        std::remove_if(listOfBullet.begin(), listOfBullet.end(), [&bullet](const auto& shoot) {
            return shoot.first == bullet;
        }),
        listOfBullet.end()
    );
}

// --------------------------------------------------------------
// Bullet
// --------------------------------------------------------------

void Bullet::draw_me(GLuint texture, std::pair<double, double> posTarget){
    // Calculer l'angle en radians entre la position actuelle et la position de la cible
    double deltaX = posTarget.first - pos.first;
    double deltaY = posTarget.second - pos.second;
    double angle = std::atan2(deltaY, deltaX) * 180.0 / M_PI; // Convertir de radians à degrés

    glPushMatrix();
        glTranslatef(pos.first, pos.second, 0);
        glRotatef(90, 0, 0, 1);
        glRotatef(angle, 0, 0, 1);
        glScalef(0.025,0.075,1);
        draw_quad_with_texture(texture);
    glPopMatrix();
}

void move_bullet(Bullet& bullet, std::pair<double,double> const& target) {
    if(bullet.pos.first > target.first) bullet.pos.first -= 0.01;
    if(bullet.pos.first < target.first) bullet.pos.first += 0.01;
    if(bullet.pos.second > target.second) bullet.pos.second -= 0.01;
    if(bullet.pos.second < target.second) bullet.pos.second += 0.01;
}