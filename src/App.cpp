#include "App.hpp"
#include "game/draws/draw.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <utility>
#include <sstream>
#include <iostream>
#include <vector>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"


std::pair<double, double> App::screen_px_to_squareScreen_px(std::pair<double, double> pos){
    pos.first = (pos.first - (_width - _height)/2)*size - (_height -(_height*size))/2;
    pos.second = pos.second*size - (_height -(_height*size))/2;
    return pos;
}

std::pair<double, double> App::squareScreen_px_to_squareScreen_abs(std::pair<double, double> pos){
    pos.first = (pos.first*2)/(((_height - (_height -(_height*size))/2))*size - (_height -(_height*size))/2) - 1.f;
    pos.second =  -(pos.second*2)/(((_height - (_height -(_height*size))/2))*size - (_height -(_height*size))/2) + 1.f;
    return pos;
}


std::pair<double, double> App::squareScreen_abs_to_SquareScreen_tiles(std::pair<double, double> pos){
    // std::cout << "First prev : " << pos.first << std::endl;
    // pos.first = (int((pos.first + 1)*_numberOfTiles/2))*(2/float(_numberOfTiles)) - 1. + 2/float(_numberOfTiles);
    pos.first = std::floor(pos.first * _numberOfTiles / 2.0) * (2.0 / _numberOfTiles);
    // pos.second = -(_numberOfTiles - int((pos.second + 1)*_numberOfTiles/2) - 1)*(2/float(_numberOfTiles)) + 1. - 2/float(_numberOfTiles);
    pos.second = std::floor(pos.second * _numberOfTiles / 2.0) * (2.0 / _numberOfTiles);
    return pos;
}


double App::transform_mouse_pos_tile_to_case_index(std::pair<double, double> pos){
    double result;

    result = (pos.first*_numberOfTiles/2.) + _numberOfTiles/2. + _numberOfTiles*(((-pos.second)*_numberOfTiles/2.) + _numberOfTiles/2.);

    return result - _numberOfTiles;
}





App::App() : _previousTime(0.0), _viewSize(2.0) {
   // load what needs to be loaded here (for example textures)

    img::Image test {img::load(make_absolute_path("images/level.png", true), 3, true)};    
    listOfEnnemyTexture.push_back(std::vector<GLuint>{loadTexture(img::load(make_absolute_path("images/Enemy/enemyTest.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/enemyTest2.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/enemyTest3.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/enemyTest4.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/enemyTest5.png", true), 4, true))});
    listOfEnnemyTexture.push_back(std::vector<GLuint>{loadTexture(img::load(make_absolute_path("images/Enemy/Golem1.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/Golem2.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/Golem3.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/Golem4.png", true), 4, true)),
                                                    loadTexture(img::load(make_absolute_path("images/Enemy/Golem5.png", true), 4, true))});

    // Load background textures
    listOfBackgroundTextures.push_back({screen_state::MAIN_MENU,img::load(make_absolute_path("images/menu_background.png", true), 3, false)});
    listOfBackgroundTextures.push_back({screen_state::PAUSE_MENU,img::load(make_absolute_path("images/pause_background.png", true), 3, false)});
    listOfBackgroundTextures.push_back({screen_state::LEVEL,img::load(make_absolute_path("images/level_background.png", true), 3, false)});
    listOfBackgroundTextures.push_back({screen_state::LOSE,img::load(make_absolute_path("images/lose_background.jpg", true), 3, false)});
    listOfBackgroundTextures.push_back({screen_state::WIN,img::load(make_absolute_path("images/win_background.jpg", true), 3, false)});
    listOfBackgroundTextures.push_back({screen_state::INFO,img::load(make_absolute_path("images/credit_background.jpg", true), 3, false)});
    

    // Load Case Texture

    //Default Cases
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/defaultTile.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/offRoadTile.png", true), 3, true));
    //Direction Cases
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/TileTopBot.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/TileLefRig.png", true), 3, true));

    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/TileBotLef.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/TileBotRig.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/TileTopLef.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/TileTopRig.png", true), 3, true));


    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/startTile.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/endTile.png", true), 3, true));

    // Random Decor
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/offRoadTile1.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/offRoadTile2.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/offRoadTile3.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/offRoadTile4.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/offRoadTile5.png", true), 3, true));
    listOfCaseImg.push_back(img::load(make_absolute_path("images/Cases/offRoadTile6.png", true), 3, true));


    for(auto && img : listOfCaseImg){
        listOfCaseTexture.push_back(loadTexture(img));
    }

    // img::Image playButton {img::load(make_absolute_path("images/playbutton.png", true), 3, true)};
    // _texture = loadTexture(playButton);
    
    ;
    // _texture = loadTexture(test);
}


void App::setup() {
    // Set the clear color to a nice blue
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    setup_drawing();

    // Setup the text renderer with blending enabled and white text color
    TextRenderer.ResetFont();
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.EnableBlending(true);

    // Création des cases
    tileSize = 2./float(_numberOfTiles);

    myScreen.create_list_of_case(listOfNodes,listOfCaseTexture);



    // Création des boutons
    listOfButtonMenu.push_back(Button{typeButton::BEGIN,std::pair<double,double>{-0.2, 0.4}, std::pair<double,double>{0.4, 0.4}, false});
    listOfButtonMenu.push_back(Button{typeButton::CREDIT,std::pair<double,double>{-0.2, -0.1}, std::pair<double,double>{0.4, 0.4}, false});
    listOfButtonMenu.push_back(Button{typeButton::QUIT,std::pair<double,double>{-0.2, -0.6}, std::pair<double,double>{0.4, 0.4}, false});
    // listOfButtonTowerLevel.push_back(Button{typeButton::PAUSE,std::pair<double,double>{-1.4, 0.1}, std::pair<double,double>{0.4, 0.2}, false});
    // listOfButtonTowerLevel.push_back(Button{typeButton::PLAY,std::pair<double,double>{-0.1, 0.1}, std::pair<double,double>{0.2, 0.2}, false});
    for (auto &&button : listOfButtonMenu) {button.set_stats_from_type();}


    // Les boutons de Tours dans LEVEL :
    listOfButtonTowerLevel.push_back(Button{typeButton::TOWER_1,std::pair<double,double>{1.1, 0.5}, std::pair<double,double>{0.2, 0.2}, false});
    listOfButtonTowerLevel.push_back(Button{typeButton::ANNULER_TOWER,std::pair<double,double>{1.05, 0.8}, std::pair<double,double>{0.1, 0.1}, false});
    listOfButtonTowerLevel.push_back(Button{typeButton::TOWER_2,std::pair<double,double>{1.1, 0.1}, std::pair<double,double>{0.2, 0.2}, false});
    listOfButtonTowerLevel.push_back(Button{typeButton::TOWER_3,std::pair<double,double>{1.1, -0.4}, std::pair<double,double>{0.2, 0.2}, false});
    listOfButtonTowerLevel.push_back(Button{typeButton::PAUSE,std::pair<double,double>{-1.5, 0.2}, std::pair<double,double>{0.3, 0.3}, false});
    for (auto &&button : listOfButtonTowerLevel) {button.set_stats_from_type();}

    // Buttons de Pause :
    listOfButtonPause.push_back(Button{typeButton::EXIT_TO_MENU,std::pair<double,double>{-0.2, -0.2}, std::pair<double,double>{0.4, 0.4}, false});
    listOfButtonPause.push_back(Button{typeButton::CONTINU,std::pair<double,double>{-0.2, 0.3}, std::pair<double,double>{0.4, 0.4}, false});
    for (auto &&button : listOfButtonPause) {button.set_stats_from_type();}

    listOfButtonEnd.push_back(Button{typeButton::QUIT,std::pair<double,double>{-0.2, -0.6}, std::pair<double,double>{0.4, 0.4}, false});
    listOfButtonCredit.push_back(Button{typeButton::EXIT_TO_MENU,std::pair<double,double>{-0.2, -0.6}, std::pair<double,double>{0.4, 0.4}, false});
    for (auto &&button : listOfButtonEnd) {button.set_stats_from_type();}
    for (auto &&button : listOfButtonCredit) {button.set_stats_from_type();}

    // Création des tours
    // listOfTower.push_back(Tower{typeTower::TYPE1,int{1}, std::pair<double,double>{-1, 0.5,}});
    // listOfTower.push_back(Tower{typeTower::TYPE2,int{2}, std::pair<double,double>{0.5, -0.2,}});
    // listOfTower.push_back(Tower{typeTower::TYPE3,int{3}, std::pair<double,double>{0.8, 0.8,}});
    // listOfTower.push_back(Tower{typeTower::TYPE4,int{4}, std::pair<double,double>{-0.1, -0.8,}});
    for (auto &&tower : listOfTower) {tower.set_stats_from_type();tower.set_range_box(tileSize);}
    
    // Création des ennemis
    listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, listOfNodes, myScreen.nbrTileSide});
    listOfEnemy.push_back(Enemy{typeEnemy::ENEMY2, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.1, 0.1, listOfNodes, myScreen.nbrTileSide});


    for(Enemy & currentEnnemy : listOfEnemy){
        currentEnnemy.init_enemy();
    }

    
}

void App::update() {

    currentTime = glfwGetTime() ;
    const double elapsedTime { currentTime - _previousTime};
    _previousTime = currentTime;


    mouse_pos = screen_px_to_squareScreen_px(mouse_pos);

    pos_mouse_abs = squareScreen_px_to_squareScreen_abs(mouse_pos);
    
    pos_tile_mouse = squareScreen_abs_to_SquareScreen_tiles(pos_mouse_abs);

    if(myScreen._state == screen_state::LEVEL){
        if(listOfEnemy.size() != 0){
            for(auto it = listOfEnemy.begin(); it != listOfEnemy.end();){
                Enemy& currentEnemy = *it;
                currentEnemy.is_walking();
                if(collision_box_box(currentEnemy.pos, {currentEnemy.width, currentEnemy.height}, listOfNodes.back().pos, {tileSize, tileSize})) {
                    it = listOfEnemy.erase(it);
                    globalLife -= 1;
                }else {
                    ++it; // Passe à l'élément suivant seulement si aucun élément n'est supprimé
                }
            }
        }
        for (auto& tower : listOfTower) {
            if (!listOfEnemy.empty()) {
                for (auto it = listOfEnemy.begin(); it != listOfEnemy.end(); ) {
                    Enemy& enemy = *it;

                    if (collision_box_box(enemy.pos, {enemy.width, enemy.height}, tower.rangeBox.first, tower.rangeBox.second) 
                        && currentTime - tower.lastTimeShoot > tower.attackSpeed) {

                        double distanceCurrentEnemy = dist_two_pos(tower.pos, enemy.pos);

                        // Si cet ennemi est plus proche que le dernier ciblé
                        if (distanceCurrentEnemy < tower.distLastEnemyTargeted) {
                            tower.idLastEnemyTargeted = enemy.id;
                            tower.distLastEnemyTargeted = distanceCurrentEnemy;
                            tower.shoot(tower.idLastEnemyTargeted, currentTime, tileSize); // On tire que si c'est l'ennemi plus proche
                        } else if (enemy.id == tower.idLastEnemyTargeted) { // Sinon si cet ennemi est le même que le dernier ciblé
                            tower.distLastEnemyTargeted = distanceCurrentEnemy;
                            tower.shoot(tower.idLastEnemyTargeted, currentTime, tileSize); // On tire que si c'est l'ennemi plus proche ou le seul présent
                        }
                    }

                    if (enemy.lifePoint <= 0) {
                        std::cout << "Enemy died" << std::endl;
                        myScreen.currency += enemy.reward;
                        it = listOfEnemy.erase(it); // Supprime l'ennemi mort et récupère un nouvel itérateur valide
                    } else {
                        ++it; // Passe à l'élément suivant seulement si aucun élément n'est supprimé
                    }
                }
            } else {
                for (auto& tower : listOfTower) {
                    tower.listOfBullet.clear();
                }
            }
        }

    }   
   
    // UwU 
    render();

    if(currentTime < 5 && currentTime > 0 && !vague1) {
        for (size_t i = 0; i < 2; i++){
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, listOfNodes, myScreen.nbrTileSide});
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY2, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.1, 0.1, listOfNodes, myScreen.nbrTileSide});
        }
        for(Enemy & currentEnnemy : listOfEnemy){currentEnnemy.init_enemy();}
        vague1 = true;
    } else if (currentTime < 10 && currentTime > 5 && !vague2) {
        for (size_t i = 0; i < 3; i++){
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, listOfNodes, myScreen.nbrTileSide});
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY2, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.1, 0.1, listOfNodes, myScreen.nbrTileSide});
        }
        for(Enemy & currentEnnemy : listOfEnemy){currentEnnemy.init_enemy();}
        vague2 = true;
    } else if (currentTime < 15 && currentTime > 10 && !vague3) {
        for (size_t i = 0; i < 4; i++){
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, listOfNodes, myScreen.nbrTileSide});
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY2, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.1, 0.1, listOfNodes, myScreen.nbrTileSide});
        }
        for(Enemy & currentEnnemy : listOfEnemy){currentEnnemy.init_enemy();}
        vague3 = true;
    } else if (currentTime < 20 && currentTime > 15 && !vague4) {
        for (size_t i = 0; i < 6; i++){
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, listOfNodes, myScreen.nbrTileSide});
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY2, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.1, 0.1, listOfNodes, myScreen.nbrTileSide});
        }
        for(Enemy & currentEnnemy : listOfEnemy){currentEnnemy.init_enemy();}
        vague4 = true;
    } else if (currentTime < 25 && currentTime > 20 && !vague5) {
        for (size_t i = 0; i < 8; i++){
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, listOfNodes, myScreen.nbrTileSide});
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY2, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.1, 0.1, listOfNodes, myScreen.nbrTileSide});
        }
        for(Enemy & currentEnnemy : listOfEnemy){currentEnnemy.init_enemy();}
        vague5 = true;
    } else if (currentTime > 25 && currentTime-lastInfiniteVague > 5) {
        for (size_t i = 0; i < (rand() % 20 + 1 + 1); i++){
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY1, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.05, 0.05, listOfNodes, myScreen.nbrTileSide});
            listOfEnemy.push_back(Enemy{typeEnemy::ENEMY2, 1, false, std::pair<double,double>{-0.99, 0.99}, 0.1, 0.1, listOfNodes, myScreen.nbrTileSide});
        }
        for(Enemy & currentEnnemy : listOfEnemy){currentEnnemy.init_enemy();}
        lastInfiniteVague = currentTime;
    }

    // std::cout << globalLife << std::endl;
    if(globalLife <= 0)myScreen._state = screen_state::LOSE;
    // std::cout << currentTime << std::endl;
    if(listOfEnemy.size() <= 0 && currentTime > 22)myScreen._state = screen_state::WIN;
}

void App::render() {
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.5,0.5,0.5,1);
    
    glPushMatrix();
        glScalef(size, size, 1);
        draw_all_content();
    glPopMatrix();



    TextRenderer.Render();
}

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/) {
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/) {
    if(currentTime - delayForAllButton > 0.2){

    std::cout << myScreen.listCase[transform_mouse_pos_tile_to_case_index(pos_tile_mouse)]._type << std::endl;
    std::cout << transform_mouse_pos_tile_to_case_index(pos_tile_mouse) << std::endl;
        if(myScreen._state == screen_state::MAIN_MENU){
            for(Button currentButton : listOfButtonMenu){
                // std::cout << "mouseX : " <<pos_mouse_abs.first << " " << "mouseY : " <<pos_mouse_abs.second << std::endl;
                // std::cout << "abscisse entre : [" << currentButton.pos.first << ", " << currentButton.pos.first + currentButton.size.first << "]" << std::endl;
                // std::cout << "ordonné entre : [" << -currentButton.pos.second << ", " << -(currentButton.pos.second - currentButton.size.second) << "]" << std::endl;

                if(collision_pos_box(pos_mouse_abs, currentButton.pos, currentButton.size)) {
                    switch (currentButton._type){
                    case BEGIN:
                        myScreen._state = screen_state::LEVEL;
                        break;
                    case QUIT:
                        // Close window
                        windowsShouldClose = true;
                        break;
                    case CREDIT:
                        // A changer
                        myScreen._state = screen_state::INFO;
                        break;
                    default:
                        break;
                    }
                }
            }
            delayForAllButton = currentTime;
        }
        else if(myScreen._state == screen_state::PAUSE_MENU){
            for(Button currentButton : listOfButtonPause){

                if(collision_pos_box(pos_mouse_abs, currentButton.pos, currentButton.size)) {
                    switch (currentButton._type){
                    case EXIT_TO_MENU:
                        myScreen._state = screen_state::MAIN_MENU;
                        break;
                    case CONTINU:
                        myScreen._state = screen_state::LEVEL;
                    default:
                        break;
                    }
                }
            }
            delayForAllButton = currentTime;
        }
        else if(myScreen._state == screen_state::LEVEL){
            for(Button currentButton : listOfButtonTowerLevel){

                if(collision_pos_box(pos_mouse_abs, currentButton.pos, currentButton.size)) {
                    switch (currentButton._type){
                    case TOWER_1:
                        if(myScreen.currency >= price.tower_1){
                            myScreen.showCaseDispo = true;
                            myScreen.currentTowerToDraw = typeTower::TYPE1;
                            delayForTowerPlacement = currentTime;
                            
                            
                        }
                        break;
                    
                    case ANNULER_TOWER:
                        myScreen.showCaseDispo = false;
                        break;
                    case TOWER_2:
                        if(myScreen.currency >= price.tower_2){
                            myScreen.showCaseDispo = true;
                            myScreen.currentTowerToDraw = typeTower::TYPE2;
                            delayForTowerPlacement = currentTime;
                            
                        }
                        break;
                    case TOWER_3:
                        if(myScreen.currency >= price.tower_3){
                            myScreen.showCaseDispo = true;
                            myScreen.currentTowerToDraw = typeTower::TYPE3;
                            delayForTowerPlacement = currentTime;
                            
                        }
                        break;
                    case PAUSE:
                        myScreen._state = screen_state::PAUSE_MENU;
                        break;
                    default:
                        break;
                    }
                }
                
            }
            
            if(myScreen.showCaseDispo && currentTime-delayForTowerPlacement > 0.2 && isFreeToBuild()){
                std::cout << transform_mouse_pos_tile_to_case_index(pos_tile_mouse) << std::endl;
                myScreen.listCase[transform_mouse_pos_tile_to_case_index(pos_tile_mouse)].occupied = true;
                switch (myScreen.currentTowerToDraw){
                    case 1:
                        myScreen.currency -= price.tower_1;
                        listOfTower.push_back(Tower{typeTower::TYPE1, idTower, pos_tile_mouse, 1});
                        break;
                    case 2:
                        myScreen.currency -= price.tower_2;
                        listOfTower.push_back(Tower{typeTower::TYPE2, idTower, pos_tile_mouse, 1});
                        break;
                    case 3:
                        myScreen.currency -= price.tower_3;
                        listOfTower.push_back(Tower{typeTower::TYPE3, idTower, pos_tile_mouse, 1});
                        break;
                }
                idTower++;
                for (auto &&tower : listOfTower) {tower.set_stats_from_type();tower.set_range_box(tileSize);}
                myScreen.showCaseDispo = false;
            }
            delayForAllButton = currentTime;
        }
        else if(myScreen._state == screen_state::INFO){
            for(Button currentButton : listOfButtonCredit){

                if(collision_pos_box(pos_mouse_abs, currentButton.pos, currentButton.size)) {
                    switch (currentButton._type){
                    case EXIT_TO_MENU:
                        myScreen._state = screen_state::MAIN_MENU;
                        break;
                    default:
                        break;
                    }
                }
            }
            delayForAllButton = currentTime;
        }
        else if(myScreen._state == screen_state::WIN || myScreen._state == screen_state::LOSE){
            for(Button currentButton : listOfButtonEnd){

                if(collision_pos_box(pos_mouse_abs, currentButton.pos, currentButton.size)) {
                    switch (currentButton._type){
                    case QUIT:
                        windowsShouldClose = true;
                        break;
                    default:
                        break;
                    }
                }
            }
            delayForAllButton = currentTime;
        }
    }

        // if(pos_mouse_abs.first > currentButton.pos.first && pos_mouse_abs.first < currentButton.pos.first + currentButton.size.first
        // && pos_mouse_abs.second > -currentButton.pos.second && pos_mouse_abs.second < -(currentButton.pos.second - currentButton.size.second))
        // {
        //     myScreen._state = screen_state::LEVEL;
        // }
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/) {
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/) {
}

void App::size_callback(int width, int height) {
    _width  = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio { _width / (float) _height };

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(aspectRatio > 1.0f) {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    } else {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}




void App::removeDeadEnemies() {
    listOfEnemy.erase(
        std::remove_if(listOfEnemy.begin(), listOfEnemy.end(), [](const auto& enemy) {
            return enemy.lifePoint <= 0;
        }),
        listOfEnemy.end()
    );
}
Enemy* App::findEnemyFromList(int wantedId) {
    auto enemyIt = std::find_if(listOfEnemy.begin(), listOfEnemy.end(), [&wantedId](const auto& enemy) {
                    return enemy.id == wantedId;
                });
    if (enemyIt != listOfEnemy.end()) {
        return &(*enemyIt);
    } else {
        return nullptr;
    }
}

void App::remove_enemy(int id) {
    auto newEnd = std::remove_if(listOfEnemy.begin(), listOfEnemy.end(), [&id](const auto& enemy) {
        return enemy.id == id;
    });
    listOfEnemy.erase(newEnd, listOfEnemy.end());
    std::cout << "worked" << std::endl;
}

bool App::isFreeToBuild(){
    return (myScreen.listCase[transform_mouse_pos_tile_to_case_index(pos_tile_mouse)]._type == typeCase::DECOR) 
    && pos_tile_mouse.first < 1.0 && pos_tile_mouse.first >= -1. && pos_tile_mouse.second < 1. && pos_tile_mouse.second >= -1. 
    && !(myScreen.listCase[transform_mouse_pos_tile_to_case_index(pos_tile_mouse)].occupied);
}

// void App::remplir_listOfCase(){
//     for(int i{0}; i < myScreen.nbrTileSide*myScreen.nbrTileSide; ++i){
//         listOfCase.push_back(Case{i, typeCase::DECOR, false, std::pair<double,double>{(i%myScreen.nbrTileSide)*(2./myScreen.nbrTileSide), (i/myScreen.nbrTileSide)*(2./myScreen.nbrTileSide)}, loadTexture(listOfCaseTexture[0].second)});
//     }
//     for(Case myCase : listOfNodes){
//         listOfCase[myCase.index] = myCase;
//     }
// }

