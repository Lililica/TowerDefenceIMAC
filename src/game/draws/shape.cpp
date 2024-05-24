
#include "shape.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "GLHelpers.hpp"
#include <iostream>

void drawRect(double xpos, double ypos, double width, double height){
        glBegin(GL_QUADS);
            glVertex2d(xpos, ypos);
            glVertex2d(xpos + width, ypos);
            glVertex2d(xpos + width, ypos + height);
            glVertex2d(xpos, ypos + height);
        glEnd();
}