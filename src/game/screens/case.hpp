#pragma once

enum typeCase { DECOR,  PATH, TOWER, START, END };

struct Case{

    int index {};
    typeCase _type {DECOR};
    bool occupied {false};
    std::pair<double,double> pos {0,0};
    
};