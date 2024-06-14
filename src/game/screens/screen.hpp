#pragma once

enum screen_state { MAIN_MENU, LEVEL, PAUSE_MENU, LEVEL_SELECTOR };

struct screen{

    screen_state _state {MAIN_MENU};


    int nbrTileSide {10};


};