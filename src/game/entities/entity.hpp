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
#include "../utilitaires/outil.hpp"
#include "GLHelpers.hpp"

enum typeTower { TYPE1, TYPE2, TYPE3, TYPE4 };
enum typeEnemy {ENEMY1, ENEMY2, ENEMY3};
enum Direction {TOP, RIGHT,BOTTOM, LEFT};

struct Enemy {

    typeEnemy type {};
    int id {0};
    bool isDead {false};

    std::pair<double,double> pos {};

    double width {};
    double height {};

    GLuint texture;

    int nbrTileSide{20};

    std::vector<Case> listOfNodes {Case{0, START, false, std::pair<double,double>{0,1 - (2./nbrTileSide)}}, 
                                Case{0, PATH, false, std::pair<double,double>{1 - 10*(2./nbrTileSide),1 - (2./nbrTileSide)}},
                                Case{0, PATH, false, std::pair<double,double>{1 - 10*(2./nbrTileSide),- 1}},
                                Case{0, PATH, false, std::pair<double,double>{1 - (2./nbrTileSide), - 1}}
                                };

    Direction direction {RIGHT};

    int itTKT {0};

    void is_walking();
    void draw_my_lp();

    int initLP {100};
    int lifePoint {100};
    double speed {0.05/15};

    int reward {0}; //combien rapporte l'ennemi a sa mort

    

    

    
    
    void draw_me();
};


struct Bullet {

    std::pair<double,double> pos {};
    
    double width {};
    double height {};
    double speed {};

};

struct Tower {

    typeTower _type {TYPE1};
    int id {0};

    std::pair<double,double> pos {0,0};

    GLuint _texture;
    int lifePoint {0};
    int power {0};
    int range {0};
    std::pair<std::pair<double,double>,std::pair<double,double>> rangeBox {pos, {0,0}};
    double attackSpeed {0.1}; //intervalle entre 2 tirs

    void set_stats_from_type();
    void set_range_box(double tileSize);
    void draw_me(double tileSize);
    void draw_range_box();

    std::vector<Bullet> listOfBullet {};

    // void remove_bullet(Bullet bullet);
};
