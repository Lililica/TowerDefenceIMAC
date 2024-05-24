#pragma once
#include <vector>

enum state { MAIN_MENU, LEVEL, PAUSE_MENU, LEVEL_SELECTOR };

struct screen{

    state _state {MAIN_MENU};
    unsigned int levelId {};
    int nbrTileSide {20};
    std::vector<Case> listCase {};


};