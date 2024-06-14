#pragma once
#include <vector>
#include "./case.hpp"
#include "./button.hpp"

enum screen_state { MAIN_MENU, LEVEL, PAUSE_MENU, LEVEL_SELECTOR };

struct Screen{

    screen_state _state {MAIN_MENU};
    unsigned int levelId {};
    int nbrTileSide {20};
    std::vector<Case> listCase {};
    std::vector<Button> listButton {};

    void create_list_of_case(std::vector<int> listTypeCase);
};