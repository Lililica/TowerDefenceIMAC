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

enum typeCase { DECOR, PATH, PATH_R_L, PATH_T_B, PATH_T_R, PATH_T_L, PATH_B_R, PATH_B_L, TOWER, START, END };

struct Case{

    int index {};
    typeCase _type {DECOR};
    bool occupied {false};
    std::pair<double,double> pos {0,0};

    // GLuint _texture {};

    void draw_me(int nbrTiles, std::vector<GLuint> listOfCaseTexture);
};