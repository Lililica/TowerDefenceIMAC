#pragma once

#include <vector>
#include <iostream>

struct Bullet {

    std::pair<double,double> pos {};
    
    size_t width {};
    size_t height {};
    double speed {};

};

enum typeTower {TOWER1, TOWER2, TOWER3};

struct Tower {

    typeTower _type {};
    int id {0};

    std::pair<double,double> pos {};

    int power {0};
    double attackSpeed {0.};  //intervalle entre 2 tirs
    int lifePoint {0};
    std::vector<Bullet> listOfBullet {};

    void remove_bullet(Bullet bullet);
};