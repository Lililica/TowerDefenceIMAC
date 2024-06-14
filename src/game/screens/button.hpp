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

enum typeButton { PAUSE, PLAY };

struct Button{

    typeButton _type {PAUSE};
    std::pair<double,double> pos {0,0};
    std::pair<double,double> size {3,2};
    bool pressed {false};
    GLuint _texture;

    void draw_me();
    
};