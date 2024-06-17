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

enum typeCase { DECOR,  PATH, TOWER, START, END };

struct Case{

    int index {};
    typeCase _type {DECOR};
    bool occupied {false};
    std::pair<double,double> pos {0,0};

    GLuint _texture {};

    void draw_me(int nbrTiles, std::vector<GLuint> listOfCaseTexture);
};