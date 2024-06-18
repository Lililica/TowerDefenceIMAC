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

enum typeButton { BEGIN, PAUSE, PLAY, RESTART, QUIT, CREDIT, TOWER_1, ANNULER_TOWER, TOWER_2, TOWER_3, EXIT_TO_MENU, CONTINU};



struct Button{

    typeButton _type {PAUSE};
    std::pair<double,double> pos {0,0};
    std::pair<double,double> size {3,2};
    bool pressed {false};
    GLuint _texture;

    void set_stats_from_type();
    void draw_me();
    
};