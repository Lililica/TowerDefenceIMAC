#pragma once
#include <utility>

bool collision_position_box(std::pair<double, double> pos, std::pair<double, double> pos_box, std::pair<double, double> size_box);
bool collision_box_box(std::pair<double, double> pos_box1, std::pair<double, double> size_box1, std::pair<double, double> pos_box2, std::pair<double, double> size_box2);