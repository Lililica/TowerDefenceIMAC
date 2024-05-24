#include "entity.hpp"

#include <iostream>
#include <vector>

void Tower::remove_bullet(Bullet bullet){
    std::remove(listOfBullet.begin(), listOfBullet.end(), bullet);
}