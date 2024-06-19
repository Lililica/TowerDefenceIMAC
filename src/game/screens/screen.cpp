#include <iostream>
#include <vector>
#include "screen.hpp"

bool AreSame(double a, double b) {
    return std::fabs(a - b) < 0.0001;
}

void Screen::create_list_of_case(std::vector<Case> & listOfNodes, std::vector<GLuint> listOfCaseTexture)  {
    for (size_t i = 0; i < nbrTileSide*nbrTileSide; ++i) {
        Case newCase {};
        newCase.index = i;
        int size {nbrTileSide};
        // switch (listTypeCase[i]) {
        //     case 0:
        //         newCase._type  =  DECOR;
        //         break;
        //     case 1:
        //         newCase._type  =  PATH;
        //         break;
        //     case 2:
        //         newCase._type  =  START;
        //         break;
        //     case 3:
        //         newCase._type  =  END;
        //         break;
        //     case 4:
        //         newCase._type  =  TOWER;
        //         break;
        //     default:
        //         newCase._type  =  DECOR;
        // }
        newCase._type = DECOR;
        double pos_x {(i%size)*(2.0/size)-1.0};
        double pos_y {(-(i/size)+size)*(2.0/size)-1.0};
        newCase.pos = {float(pos_x), float(pos_y)};

        this->listCase.push_back(newCase);
    }
    for(int i{0}; i < listOfNodes.size()-2; ++i){
                if(float(listOfNodes[i].pos.first) == float(listOfNodes[i+1].pos.first) && float(listOfNodes[i].pos.second) > float(listOfNodes[i+1].pos.second)){
                    if(float(listOfNodes[i+1].pos.second) == float(listOfNodes[i+2].pos.second) && float(listOfNodes[i+1].pos.first) < float(listOfNodes[i+2].pos.first)){
                        listOfNodes[i+1]._type = typeCase::PATH_T_R;
                    }
                    if(float(listOfNodes[i+1].pos.second) == float(listOfNodes[i+2].pos.second) && float(listOfNodes[i+1].pos.first) > float(listOfNodes[i+2].pos.first)){
                        listOfNodes[i+1]._type = typeCase::PATH_T_L;
                    }
                }else if(float(listOfNodes[i].pos.first) == float(listOfNodes[i+1].pos.first) && float(listOfNodes[i].pos.second) < float(listOfNodes[i+1].pos.second)){
                    if(float(listOfNodes[i+1].pos.second) == float(listOfNodes[i+2].pos.second) && float(listOfNodes[i+1].pos.first) < float(listOfNodes[i+2].pos.first)){
                        listOfNodes[i+1]._type = typeCase::PATH_B_R;
                    }
                    if(float(listOfNodes[i+1].pos.second) == float(listOfNodes[i+2].pos.second) && float(listOfNodes[i+1].pos.first) > float(listOfNodes[i+2].pos.first)){
                        listOfNodes[i+1]._type = typeCase::PATH_B_L;
                    }
                }else if(float(listOfNodes[i].pos.second) == float(listOfNodes[i+1].pos.second) && float(listOfNodes[i].pos.first) < float(listOfNodes[i+1].pos.first)){
                    if(float(listOfNodes[i+1].pos.first) == float(listOfNodes[i+2].pos.first) && float(listOfNodes[i+1].pos.second) < float(listOfNodes[i+2].pos.second)){
                        listOfNodes[i+1]._type = typeCase::PATH_T_L;
                    }
                    if(float(listOfNodes[i+1].pos.first) == float(listOfNodes[i+2].pos.first) && float(listOfNodes[i+1].pos.second) > float(listOfNodes[i+2].pos.second)){
                        listOfNodes[i+1]._type = typeCase::PATH_B_L;
                    }
                }else if(float(listOfNodes[i].pos.second) == float(listOfNodes[i+1].pos.second) && float(listOfNodes[i].pos.first) > float(listOfNodes[i+1].pos.first)){
                    if(float(listOfNodes[i+1].pos.first) == float(listOfNodes[i+2].pos.first) && float(listOfNodes[i+1].pos.second) < float(listOfNodes[i+2].pos.second)){
                        listOfNodes[i+1]._type = typeCase::PATH_T_R;
                    }
                    if(float(listOfNodes[i+1].pos.first) == float(listOfNodes[i+2].pos.first) && float(listOfNodes[i+1].pos.second) > float(listOfNodes[i+2].pos.second)){
                        listOfNodes[i+1]._type = typeCase::PATH_B_R;
                    }
                }
    }
    for(Case & myCase : listOfNodes){
        listCase[myCase.index] = myCase;
        (listCase[myCase.index].pos.second>0)?(listCase[myCase.index].pos.second+=0.1):(listCase[myCase.index].pos.second+=0.1);
        myCase.pos.second += 0.1; 
    }
    for(int i{0}; i < listOfNodes.size()-1; ++i){
        // std::string debug;
        for(Case & myCase : listCase){
            if(myCase._type == typeCase::DECOR ){ //&& myCase._type != typeCase::PATH_B_L && myCase._type != typeCase::PATH_B_R  && myCase._type != typeCase::PATH_B_L  && myCase._type != typeCase::PATH_T_R  && myCase._type != typeCase::PATH_T_L
                if(AreSame((listOfNodes[i].pos.first), (listOfNodes[i+1].pos.first)) &&  (listOfNodes[i].pos.second) > ((listOfNodes[i+1].pos.second))){
                    // debug = ((myCase.pos.first) == listOfNodes[i].pos.first) ? " oui" : " non";
                    // std::cout << "Case : " << (myCase.pos.first) << debug << " C ca a la base : " << listOfNodes[i].pos.first <<std::endl;
                    // // std::cout << "caseX : " << (myCase.pos.first) << " =? " << listOfNodes[i].pos.first <<" et " << "caseX : " << myCase.pos.second << " >=? " << (listOfNodes[i+1].pos.second) << std::endl;
                    if(AreSame((myCase.pos.first), (listOfNodes[i].pos.first)) && (myCase.pos.second) >= (listOfNodes[i+1].pos.second) && (myCase.pos.second) < (listOfNodes[i].pos.second) && myCase._type != typeCase::START){
                        myCase._type = typeCase::PATH_T_B;
                    }
                }else if(AreSame(listOfNodes[i].pos.first , listOfNodes[i+1].pos.first) && listOfNodes[i].pos.second < (listOfNodes[i+1].pos.second)){
                    if(myCase.index == 81) {
                        std::cout << std::endl;
                    }
                    if(AreSame((myCase.pos.first), (listOfNodes[i].pos.first)) && (myCase.pos.second) < (listOfNodes[i+1].pos.second) && (myCase.pos.second) >= (listOfNodes[i].pos.second) && myCase._type != typeCase::START){
                        myCase._type = typeCase::PATH_T_B;
                    }
                }else if(AreSame(listOfNodes[i].pos.second , (listOfNodes[i+1].pos.second)) && (listOfNodes[i].pos.first) < listOfNodes[i+1].pos.first){
                    if(AreSame((myCase.pos.second) , (listOfNodes[i].pos.second)) && (myCase.pos.first) < (listOfNodes[i+1].pos.first) && (myCase.pos.first) > (listOfNodes[i].pos.first) && myCase._type != typeCase::START){
                        myCase._type = typeCase::PATH_R_L;
                    }
                }else if(AreSame((listOfNodes[i].pos.second) , (listOfNodes[i+1].pos.second)) && (listOfNodes[i].pos.first) > (listOfNodes[i+1].pos.first)){
                    if(AreSame((myCase.pos.second) , (listOfNodes[i].pos.second)) && (myCase.pos.first) > (listOfNodes[i+1].pos.first) && (myCase.pos.first) < (listOfNodes[i].pos.first) && myCase._type != typeCase::START){
                        myCase._type = typeCase::PATH_R_L;
                    }
                }
            }
        }

    }
    for(Case & myCase : listCase){
        myCase.set_up_draw(listOfCaseTexture);
    }
    
}