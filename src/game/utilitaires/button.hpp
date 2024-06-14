#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>
#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

struct Button{

    float posX;
    float posY;

    float width;
    float height;

    GLuint texture;

    bool isPressed;

    void draw_me();

};