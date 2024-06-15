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
enum typeEnnemy {ENNEMY1, ENNEMY2, ENNEMY3};
enum Direction {TOP, RIGHT,BOTTOM, LEFT};

struct Bullet {

    std::pair<double,double> pos {};
    
    size_t width {};
    size_t height {};
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
    double attackSpeed {0.1}; //intervalle entre 2 tirs

    void set_stats_from_type();
    void draw_me(double tileSize);
    void draw_range(double tileSize);

    std::vector<Bullet> listOfBullet {};

    void remove_bullet(Bullet bullet);
};

struct Ennemy {

    typeEnnemy type {};
    int id {0};
    bool isDead {false};

    std::pair<double,double> pos {};

    double width {};
    double height {};

    GLuint texture;

    int nbrTileSide{20};

    std::vector<Case> listOfNodes {Case{0, START, false, std::pair<double,double>{0,0}}, 
                                Case{0, PATH, false, std::pair<double,double>{1 - (2/nbrTileSide),0}},
                                Case{0, PATH, false, std::pair<double,double>{1 - (2/nbrTileSide),1 - (2/nbrTileSide)}}
                                };

    Direction direction {RIGHT};

    int itTKT {0};

    void is_walking();

    int lifePoint {100};
    double speed {0.02/10};

    int reward {0}; //combien rapporte l'ennemi a sa mort

    

    

    
    
    void draw_me();
};