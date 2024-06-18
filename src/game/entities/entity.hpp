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

enum typeTower { TYPE1 = 1, TYPE2 = 2, TYPE3 = 3, TYPE4 = 4};
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
    std::vector<Case> listOfNodes;
   
    int nbrTileSide{20};

    
    Direction direction {RIGHT};

    int itTKT {0};

    void is_walking();
    void draw_my_lp();

    int initLP {300};
    int lifePoint {initLP};
    double speed {0.05/15};

    int reward {0}; //combien rapporte l'ennemi a sa mort
    
    void draw_me();
};


struct Bullet {

    std::pair<double,double> pos {};
    
    double width {};
    double height {};
    double speed {};
    double lastTimeMoved {0};

    bool operator==(const Bullet& otherBullet) const {
        return pos.first == otherBullet.pos.first &&
            pos.second == otherBullet.pos.second &&
            width == otherBullet.width &&
            height == otherBullet.height &&
            speed == otherBullet.speed &&
            lastTimeMoved == otherBullet.lastTimeMoved;
    }

    void draw_me(GLuint texture, std::pair<double, double> posTarget);
};
// bool operator==(Bullet const& bullet1, Bullet const& bullet2) {
//     return (
//         bullet1.pos.first == bullet2.pos.first &&
//         bullet1.pos.second == bullet2.pos.second &&
//         bullet1.width == bullet2.width &&
//         bullet1.height == bullet2.height &&
//         bullet1.speed == bullet2.speed &&
//         bullet1.lastTimeMoved == bullet2.lastTimeMoved
//     ) ? true : false;
// }

struct Tower {

    typeTower _type {TYPE1};
    int id {0};

    std::pair<double,double> pos {0,0};

    GLuint _texture;
    GLuint _bulletTexture;
    int lifePoint {0};
    int power {2};
    int range {0};
    std::pair<std::pair<double,double>,std::pair<double,double>> rangeBox {pos, {0,0}};
    double attackSpeed {0.2}; //intervalle entre 2 tirs
    double lastTimeShoot {0};

    void set_stats_from_type();
    void set_range_box(double tileSize);
    void draw_me(double tileSize);
    void draw_range_box();

    // Pair de balles et de l'id de l'enemy de destination
    std::vector<std::pair<Bullet, int>> listOfBullet {};

    void remove_bullet(const Bullet& bullet);

    // void lance_bullet(int nbrTiles);
};

void move_bullet(Bullet& bullet, std::pair<double,double> const& target);