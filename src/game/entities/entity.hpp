#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>
#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

enum Ennemy_Class {Gobelin};

struct Ennemy{

    Ennemy_Class type;

    int lifePoint;
    std::pair<float, float> pos;
    float speed;
    std::pair<float, float> taille;

    GLuint texture;

    void draw_me();


};