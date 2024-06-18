#pragma once
#include <utility>
#include <math.h>

double dist_two_pos(std::pair<double, double> pos1, std::pair<double, double> pos2);
bool collision_pos_box(std::pair<double, double> pos, std::pair<double, double> pos_box, std::pair<double, double> size_box);
bool collision_box_box(std::pair<double, double> pos_box1, std::pair<double, double> size_box1, std::pair<double, double> pos_box2, std::pair<double, double> size_box2);