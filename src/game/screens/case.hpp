#pragma once

#include "game/screens/screen.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>


#include <sstream>
#include <iostream>
#include <vector>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

enum typeCase { DECOR = 0, PATH = 1, PATH_R_L = 2, PATH_T_B = 3, PATH_T_R = 4, PATH_T_L = 5, PATH_B_R = 6, PATH_B_L = 7, TOWER = 8, START = 9, END = 10};

struct Case{

    int index {};
    typeCase _type {DECOR};
    bool occupied {false};
    std::pair<double,double> pos {0,0};

    GLuint _texture;

    void set_up_draw(std::vector<GLuint> listOfCaseTexture);
    void draw_me(int nbrTiles);
};