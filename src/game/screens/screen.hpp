#pragma once

#include "case.hpp"
#include "button.hpp"

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

enum screen_state { MAIN_MENU, LEVEL, PAUSE_MENU, LEVEL_SELECTOR };

struct Case;

struct Screen{

    screen_state _state {MAIN_MENU};
    unsigned int levelId {};
    int nbrTileSide {20};
    std::vector<Case> listCase {};
    std::vector<Button> listButton {};

    bool showCaseDispo {false};

    int currentTowerToDraw;

    int currency {1000};

    void create_list_of_case(std::vector<Case> listOfNodes, std::vector<GLuint> listOfCaseTexture);
};

