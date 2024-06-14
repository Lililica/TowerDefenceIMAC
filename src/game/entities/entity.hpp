#pragma once

#include "../screens/screen.hpp"

#include <vector>
#include <iostream>
#include <queue>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>
#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

enum typeTower {TOWER1, TOWER2, TOWER3};
enum typeEnnemy {ENNEMY1, ENNEMY2, ENNEMY3};
enum Direction {TOP, RIGHT,BOTTOM, LEFT};

struct Bullet {

    std::pair<double,double> pos {};
    
    size_t width {};
    size_t height {};
    double speed {};

};

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

struct Ennemy {

    typeEnnemy type {};
    int id {0};
    bool isDead {false};

    std::pair<double,double> pos {};

    Direction direction {RIGHT};
    void is_walking();

    int lifePoint {0};
    double speed {0.};
    size_t width {};
    size_t height {};
    int reward {0}; //combien rapporte l'ennemi a sa mort

    std::queue<Case> listOfNodes {};

    GLuint texture;
    
    void draw_me();
};