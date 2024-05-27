#include <iostream>
#include <vector>
#include "screen.hpp"

void Screen::create_list_of_case(std::vector<int> listTypeCase)  {
    for (size_t i = 0; i < listTypeCase.size(); ++i) {
        Case newCase {};
        newCase.index = i;
        int size {nbrTileSide};
        switch (listTypeCase[i]) {
            case 0:
                newCase._type  =  DECOR;
                break;
            case 1:
                newCase._type  =  PATH;
                break;
            case 2:
                newCase._type  =  START;
                break;
            case 3:
                newCase._type  =  END;
                break;
            case 4:
                newCase._type  =  TOWER;
                break;
            default:
                newCase._type  =  DECOR;
        }
        double pos_x {(i%size)*(2.0/size)-1.0};
        double pos_y {(-(i/size)+size)*(2.0/size)-1.0};
        newCase.pos = {pos_x, pos_y};

        this->listCase.push_back(newCase);
    }
}