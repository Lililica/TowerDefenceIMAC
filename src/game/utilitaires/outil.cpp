#include "./outil.hpp"

bool collision_pos_box(std::pair<double, double> pos, std::pair<double, double> pos_box, std::pair<double, double> size_box) {
    if(pos.first >= pos_box.first 
        && pos.first <= pos_box.first+size_box.first
        && pos.second >= pos_box.second 
        && pos.second <= pos_box.second+size_box.second)
        return true;
    else return false;
}
// bool collision_box_box(std::pair<double, double> pos_box1, std::pair<double, double> size_box1, std::pair<double, double> pos_box2, std::pair<double, double> size_box2) {
//     if(
//         pos_box1.first+size_box1.first >= pos_box2.first && 
//             (pos_box1.second+size_box1.second <= pos_box2.second 
//             || pos_box1.second >= pos_box2.second+size_box2.second)
//         || pos_box1.first <= pos_box2.first+size_box2.first &&
//             (pos_box1.second+size_box1.second <= pos_box2.second 
//             || pos_box1.second >= pos_box2.second+size_box2.second) 
//     ) return true;
//     else return false;
// }
bool collision_box_box(std::pair<double, double> pos_box1, std::pair<double, double> size_box1, std::pair<double, double> pos_box2, std::pair<double, double> size_box2) {
    if (
        pos_box1.first + size_box1.first < pos_box2.first || // Boîte 1 à gauche de la boîte 2
        pos_box1.first > pos_box2.first + size_box2.first || // Boîte 1 à droite de la boîte 2
        pos_box1.second + size_box1.second < pos_box2.second || // Boîte 1 au-dessus de la boîte 2
        pos_box1.second > pos_box2.second + size_box2.second // Boîte 1 en dessous de la boîte 2
    ) {
        return false;
    } else {
        return true;
    }
}
