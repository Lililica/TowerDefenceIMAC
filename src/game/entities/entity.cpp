#include "entity.hpp"

#include <iostream>
#include <vector>
#include <queue>

// void Tower::remove_bullet(Bullet bullet){
//     std::remove(listOfBullet.begin(), listOfBullet.end(), bullet);
// }

void Ennemy::is_walking(){

    Case case1 {listOfNodes.front()};       
    Case case2 {listOfNodes.front()};


    if(case1.pos.first == case2.pos.first && case1.pos.second < case2.pos.second){
        direction = Direction::RIGHT;
    }else if(case1.pos.first == case2.pos.first && case1.pos.second > case2.pos.second){
        direction = Direction::LEFT;
    }else if(case1.pos.second == case2.pos.second && case1.pos.first < case2.pos.first){
        direction = Direction::BOTTOM;
    }else if(case1.pos.second == case2.pos.second && case1.pos.first < case2.pos.first){
        direction = Direction::TOP;
    }

    if(pos.first == case2.pos.first && pos.second == case2.pos.second){   //A MODIFIER
        listOfNodes.pop();
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
        glTranslatef(pos.first, -pos.second,0);
        glScalef(width,-height,1);
        draw_quad_with_texture(texture);
    glPushMatrix();
}