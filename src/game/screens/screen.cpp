#include <iostream>
#include <vector>
#include "screen.hpp"

void Screen::create_list_of_case(std::vector<Case> listOfNodes, std::vector<GLuint> listOfCaseTexture)  {
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
                if(listOfNodes[i].pos.first == listOfNodes[i+1].pos.first && listOfNodes[i].pos.second > listOfNodes[i+1].pos.second){
                    if(listOfNodes[i+1].pos.second == listOfNodes[i+2].pos.second && listOfNodes[i+1].pos.first < listOfNodes[i+2].pos.first){
                        listOfNodes[i+1]._type = typeCase::PATH_T_R;
                    }
                    if(listOfNodes[i+1].pos.second == listOfNodes[i+2].pos.second && listOfNodes[i+1].pos.first > listOfNodes[i+2].pos.first){
                        listOfNodes[i+1]._type = typeCase::PATH_T_L;
                    }
                }else if(listOfNodes[i].pos.first == listOfNodes[i+1].pos.first && listOfNodes[i].pos.second < listOfNodes[i+1].pos.second){
                    if(listOfNodes[i+1].pos.second == listOfNodes[i+2].pos.second && listOfNodes[i+1].pos.first < listOfNodes[i+2].pos.first){
                        listOfNodes[i+1]._type = typeCase::PATH_B_R;
                    }
                    if(listOfNodes[i+1].pos.second == listOfNodes[i+2].pos.second && listOfNodes[i+1].pos.first > listOfNodes[i+2].pos.first){
                        listOfNodes[i+1]._type = typeCase::PATH_B_L;
                    }
                }else if(listOfNodes[i].pos.second == listOfNodes[i+1].pos.second && listOfNodes[i].pos.first < listOfNodes[i+1].pos.first){
                    if(listOfNodes[i+1].pos.first == listOfNodes[i+2].pos.first && listOfNodes[i+1].pos.second < listOfNodes[i+2].pos.second){
                        listOfNodes[i+1]._type = typeCase::PATH_T_L;
                    }
                    if(listOfNodes[i+1].pos.first == listOfNodes[i+2].pos.first && listOfNodes[i+1].pos.second > listOfNodes[i+2].pos.second){
                        listOfNodes[i+1]._type = typeCase::PATH_B_L;
                    }
                }else if(listOfNodes[i].pos.second == listOfNodes[i+1].pos.second && listOfNodes[i].pos.first > listOfNodes[i+1].pos.first){
                    if(listOfNodes[i+1].pos.first == listOfNodes[i+2].pos.first && listOfNodes[i+1].pos.second < listOfNodes[i+2].pos.second){
                        listOfNodes[i+1]._type = typeCase::PATH_T_R;
                    }
                    if(listOfNodes[i+1].pos.first == listOfNodes[i+2].pos.first && listOfNodes[i+1].pos.second > listOfNodes[i+2].pos.second){
                        listOfNodes[i+1]._type = typeCase::PATH_B_R;
                    }
                }
    }
    for(Case myCase : listOfNodes){
        listCase[myCase.index] = myCase;
    }
    for(int i{0}; i < listOfNodes.size()-1; ++i){
        std::string debug;
        for(Case & myCase : listCase){
            if(myCase._type == typeCase::DECOR ){ //&& myCase._type != typeCase::PATH_B_L && myCase._type != typeCase::PATH_B_R  && myCase._type != typeCase::PATH_B_L  && myCase._type != typeCase::PATH_T_R  && myCase._type != typeCase::PATH_T_L
                if(listOfNodes[i].pos.first == listOfNodes[i+1].pos.first &&  listOfNodes[i].pos.second > float(listOfNodes[i+1].pos.second)){
                    // debug = (float(myCase.pos.first) == listOfNodes[i].pos.first) ? " oui" : " non";
                    // std::cout << "Case : " << float(myCase.pos.first) << debug << " C ca a la base : " << listOfNodes[i].pos.first <<std::endl;
                    // // std::cout << "caseX : " << float(myCase.pos.first) << " =? " << listOfNodes[i].pos.first <<" et " << "caseX : " << myCase.pos.second << " >=? " << float(listOfNodes[i+1].pos.second) << std::endl;
                    if(float(myCase.pos.first) == float(listOfNodes[i].pos.first) && float(myCase.pos.second) >= float(listOfNodes[i+1].pos.second) && float(myCase.pos.second) < float(listOfNodes[i].pos.second)){
                        myCase._type = typeCase::PATH_T_B;
                    }
                }else if(listOfNodes[i].pos.first == listOfNodes[i+1].pos.first && listOfNodes[i].pos.second < float(listOfNodes[i+1].pos.second)){
                    if(float(myCase.pos.first) == float(listOfNodes[i].pos.first) && float(myCase.pos.second) < float(listOfNodes[i+1].pos.second) && float(myCase.pos.second) >= float(listOfNodes[i].pos.second)){
                        myCase._type = typeCase::PATH_T_B;
                    }
                }else if(listOfNodes[i].pos.second == float(listOfNodes[i+1].pos.second) && float(listOfNodes[i].pos.first) < listOfNodes[i+1].pos.first){
                    if(float(myCase.pos.second) == float(listOfNodes[i].pos.second) && float(myCase.pos.first) < float(listOfNodes[i+1].pos.first) && float(myCase.pos.first) > float(listOfNodes[i].pos.first) && myCase._type != typeCase::START){
                        myCase._type = typeCase::PATH_R_L;
                    }
                }else if(float(listOfNodes[i].pos.second) == float(listOfNodes[i+1].pos.second) && float(listOfNodes[i].pos.first) > float(listOfNodes[i+1].pos.first)){
                    if(float(myCase.pos.second) == float(listOfNodes[i].pos.second) && float(myCase.pos.first) > float(listOfNodes[i+1].pos.first) && float(myCase.pos.first) < float(listOfNodes[i].pos.first) && myCase._type != typeCase::START){
                        myCase._type = typeCase::PATH_R_L;
                    }
                }
            }
        }
        for(Case & myCase : listCase){
            myCase.set_up_draw(listOfCaseTexture);
        }
    }
}