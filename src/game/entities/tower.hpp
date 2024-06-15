#pragma once
#include <string>
#include "../utilitaires/outil.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>
#include <sstream>
#include <iostream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

enum typeTower { TYPE1, TYPE2, TYPE3, TYPE4 };

struct Tower{

    typeTower _type {TYPE1};
    int id {0};
    std::pair<double,double> pos {0,0};
    GLuint _texture;
    int lifePoint {0};
    int power {0};
    int range {0};
    int attackSpeed {0};

    void set_stats_from_type();
    void draw_me();
    void draw_range();
    
};