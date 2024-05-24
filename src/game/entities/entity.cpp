#include "entity.hpp"

#include <iostream>
#include <vector>

void Tower::remove_bullet(Bullet bullet){
    std::remove(listOfBullet.begin(), listOfBullet.end(), bullet);
}

void Ennemy::is_walking(){

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