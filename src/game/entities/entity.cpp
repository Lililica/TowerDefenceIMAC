#include "entity.hpp"

#include <iostream>
#include <vector>
#include <queue>

// void Tower::remove_bullet(Bullet bullet){
//     std::remove(listOfBullet.begin(), listOfBullet.end(), bullet);
// }

void Ennemy::is_walking(){

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

void Ennemy::draw_me(){
    glPushMatrix();
        glTranslatef(pos.first, pos.second - height,0);
        glScalef(width,-height,1);
        draw_quad_with_texture(texture);
    glPopMatrix();
}