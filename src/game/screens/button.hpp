#pragma once
#include <string>
#include "../utilitaires/outil.hpp"

enum typeButton { PAUSE, PLAY };

struct Button{

    typeButton _type {PAUSE};
    std::pair<double,double> pos {0,0};
    std::pair<double,double> size {3,2};
    bool pressed {false};
    std::string text {"Placeholder"};
    
};