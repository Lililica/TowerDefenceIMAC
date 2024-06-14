#pragma once

enum state { MAIN_MENU, LEVEL, PAUSE_MENU, LEVEL_SELECTOR };

struct screen{

    state _state {LEVEL};


    int nbrTileSide {20};


};

enum typeCase { DECOR,  PATH, TOWER, START, END };

struct Case{

    int index {};
    typeCase _type {DECOR};
    bool occupied {false};
    std::pair<double,double> pos {0,0};
};