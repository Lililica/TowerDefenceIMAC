
#include "../../App.hpp"
#include "shape.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"
#include "game/utilitaires/outil.hpp"
#include "game/entities/entity.hpp"
#include <game/draws/draw.hpp>
#include <iostream>

void setup_drawing(){
    return;
}

void App::draw_background(screen_state const& Screen) {
    std::pair<double, double> globalCoords {squareScreen_px_to_squareScreen_abs(screen_px_to_squareScreen_px({_width, _height}))};
    double width {abs(globalCoords.first*2)};
    double height {abs(globalCoords.second*2)};

    //-------------------ratio image 16/9

    auto menuBg {std::find_if(listOfBackgroundTextures.begin(), listOfBackgroundTextures.end(), [Screen](const auto& img) {
                    return img.first == Screen;
                })};
    if (menuBg != listOfBackgroundTextures.end()) {
        
        glPushMatrix();
            if(height*16/width > 9) { //si plus haut que l'image doit dépasser horizontalement
                width = height*16/9;
                glTranslatef(-width/2, height/2, 0);
                glScalef(width, height, 1.0f);
            } else { //sinon plus large que l'image doit dépasser verticalement
                height = width*9/16;
                glTranslatef(-width/2, height/2, 0);
                glScalef(width, height, 1.0f);
            }
            draw_quad_with_texture(loadTexture(menuBg->second));
        glPopMatrix();

    } else {
        std::cout << Screen << " image not found!" << std::endl;
    }
}




void App::draw_all_content(){
    double tileSize {2/float(_numberOfTiles)};
    std::string print_screen_state {};

    // ---------------------------------------------------
    // MAIN MENU
    // ---------------------------------------------------
    if(myScreen._state == screen_state::MAIN_MENU){
        // print_screen_state = "MAIN MENU";

        draw_background(screen_state::MAIN_MENU);

        for(Button button : listOfButtonMenu){
            button.draw_me();
        }
    }

    // ---------------------------------------------------
    // PAUSE MENU
    // ---------------------------------------------------
    if(myScreen._state == screen_state::PAUSE_MENU){
        // print_screen_state = "PAUSE MENU";

        draw_background(screen_state::PAUSE_MENU);

        for(Button button : listOfButtonPause){
            button.draw_me();
        }
    }

    // ---------------------------------------------------
    // LEVELS
    // ---------------------------------------------------
    if(myScreen._state == screen_state::LEVEL){
        // print_screen_state = "LEVEL";

        draw_background(screen_state::LEVEL);

        for(Case myCase : myScreen.listCase){
            myCase.draw_me(_numberOfTiles);
        }
        

        glColor3f(1.0f, 0.0f, 0.0f);
        drawRect(listOfNodes.back().pos.first, listOfNodes.back().pos.second+0.0125,tileSize,0.0125);
        glColor3f(0.0f, 1.0f, 0.0f);
        drawRect(listOfNodes.back().pos.first, listOfNodes.back().pos.second+0.0125,globalLife*tileSize/3,0.0125);


        if(listOfTower.size() != 0) {
            for(Tower tower : listOfTower){
                tower.draw_range_box();
            }
            for(Tower tower : listOfTower){
                tower.draw_me(tileSize);
            }
            for (Tower& tower : listOfTower) {
                if (!tower.listOfBullet.empty()) {
                    auto it = tower.listOfBullet.begin();
                    while (it != tower.listOfBullet.end()) {
                        auto& shoot = *it;
                        Enemy* enemy = findEnemyFromList(shoot.second);

                        if (enemy != nullptr) {
                            if (currentTime - shoot.first.lastTimeMoved >= shoot.first.speed) {
                                move_bullet(shoot.first, enemy->pos);
                            }

                            if (collision_box_box(enemy->pos, {enemy->height, enemy->width}, shoot.first.pos, {shoot.first.width, shoot.first.height})) {
                                enemy->lifePoint -= tower.power;
                                it = tower.listOfBullet.erase(it); // Supprime la balle et passe à l'élément suivant
                            } else {
                                shoot.first.draw_me(tower._bulletTexture, enemy->pos);
                                ++it; // Passe à l'élément suivant dans le vecteur de balles
                            }
                        } else {
                            std::cout << "No target found" << std::endl;
                            it = tower.listOfBullet.erase(it); // Supprime la balle et passe à l'élément suivant
                        }
                    }
                }
            }
        }

        if(listOfEnemy.size() != 0) {
            for(Enemy enemy : listOfEnemy){
                enemy.draw_me(listOfEnnemyTexture, currentTime, itAnimation, intervalForAnim);
                enemy.draw_my_lp();
            }
        }




        for(Button button : listOfButtonTowerLevel){
            if(button._type != typeButton::ANNULER_TOWER){
                std::string currencyText {};
                std::stringstream streamForCurrency {};
                SimpleText::Color color {SimpleText::Color::BLACK};
                switch (button._type)
                {
                case typeButton::TOWER_1:
                    if(myScreen.currency < price.tower_1) color = SimpleText::Color::RED;
                    streamForCurrency << std::fixed << std::setprecision(0) << price.tower_1 << "$";
                    break;
                case typeButton::TOWER_2:
                    if(myScreen.currency < price.tower_2) color = SimpleText::Color::RED;
                    streamForCurrency << std::fixed << std::setprecision(0) << price.tower_2 << "$";
                    break;
                case typeButton::TOWER_3:
                    if(myScreen.currency < price.tower_3) color = SimpleText::Color::RED;
                    streamForCurrency << std::fixed << std::setprecision(0) << price.tower_3 << "$";
                    break;
                default:
                    break;
                }
                currencyText = streamForCurrency.str();
                TextRenderer.SetColor(SimpleText::ForegroundBackground::TEXT_COLOR, color);
                TextRenderer.SetTextSize(SimpleText::FontSize::SIZE_32);
                TextRenderer.Label(currencyText.c_str(), (_width/2.) + (button.pos.first - button.size.first - 0.3)*(_width/2.) , (-button.pos.second + 0.1 )*(_height/2.)*0.9 + (_height/2.), SimpleText::CENTER);
                button.draw_me();
            }   
        }

        if(myScreen.showCaseDispo){
            for(Case myCase : myScreen.listCase){
                if((myCase._type == typeCase::DECOR && !myCase.occupied)){
                    glPushMatrix();
                        glColor4f(1,0,0,0.9*abs(sin(currentTime*3)));
                        // glScalef(0.95,0.95,1);
                        drawRect((myCase.pos.first), (myCase.pos.second), 2./myScreen.nbrTileSide, -2./myScreen.nbrTileSide);
                    glPopMatrix();    
                }
            }
            for(Button button : listOfButtonTowerLevel){
                if(button._type == typeButton::ANNULER_TOWER){
                    button.draw_me();
                    
                }   
            }

        }

        std::string currencyText {};
        std::stringstream streamForCurrency {};
        streamForCurrency << std::fixed << "Money : " << std::setprecision(2) << myScreen.currency;
        currencyText = streamForCurrency.str();
        TextRenderer.SetColor(SimpleText::ForegroundBackground::TEXT_COLOR,SimpleText::Color::RED);
        TextRenderer.SetTextSize(SimpleText::FontSize::SIZE_32);
        TextRenderer.Label(currencyText.c_str(), (0.85)*_width, 100, SimpleText::CENTER);

        
        // ---------------------------------------------------
        // Draw debug
        // ---------------------------------------------------

            // std::string debug_tiles_pos_text {};
            // std::stringstream stream {};
            // stream << std::fixed << "Tile MouseX: " << std::setprecision(2) << pos_tile_mouse.first << " et Tile MouseY: " << std::setprecision(2) << pos_tile_mouse.second;
            // debug_tiles_pos_text = stream.str();
            // TextRenderer.Label(debug_tiles_pos_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

            // if(pos_tile_mouse.first > -1. && pos_tile_mouse.first <= 1.01 && pos_tile_mouse.second >= -1.01 && pos_tile_mouse.second < 1.){
            //     glPushMatrix();
            //         glColor3f(0.0f, 0.0f, 1.0f);
            //         drawRect(pos_tile_mouse.first, pos_tile_mouse.second, -tileSize, tileSize);
            //     glPopMatrix();
            // }
            if (collision_pos_box({pos_tile_mouse.first,pos_tile_mouse.second},{-1,-1},{1.999,1.999})) {
                glPushMatrix();
                    glColor4f(0.0f, 0.0f, 1.0f, 0.4);
                    drawRect(pos_tile_mouse.first, pos_tile_mouse.second, tileSize, tileSize);
                glPopMatrix();
            }

        // ---------------------------------------------------
        // Draw Lines
        // ---------------------------------------------------

            // glColor3f(1.0f, 1.0f, 1.0f);
            // glBegin(GL_LINES);
            // for(int i{0}; i < _numberOfTiles + 1; i++){
            //     glVertex2f((2*i/float(_numberOfTiles)-1.), -1.f);
            //     glVertex2f((2*i/float(_numberOfTiles)-1.), 1.f);
            //     glVertex2f(-1.f, (2*i/float(_numberOfTiles)-1.));
            //     glVertex2f(1.f, (2*i/float(_numberOfTiles)-1.));
            // }
            // glEnd();
    }

    // ---------------------------------------------------
    // END
    // ---------------------------------------------------
    if(myScreen._state == screen_state::LOSE){
        // print_screen_state = "LOSE";

        draw_background(screen_state::LOSE);

        for(Button button : listOfButtonEnd){
            button.draw_me();
        }

        std::string currencyText {};
        std::stringstream streamForCurrency {};
        streamForCurrency << std::fixed << "YOU LOST";
        currencyText = streamForCurrency.str();
        TextRenderer.SetColor(SimpleText::ForegroundBackground::TEXT_COLOR,SimpleText::Color::RED);
        TextRenderer.SetTextSize(SimpleText::FontSize::SIZE_48);
        TextRenderer.Label(currencyText.c_str(), (0.5)*_width, 300, SimpleText::CENTER);
    }
    // ---------------------------------------------------
    // WIN
    // ---------------------------------------------------
    if(myScreen._state == screen_state::WIN){
        // print_screen_state = "WIN";

        draw_background(screen_state::WIN);

        for(Button button : listOfButtonEnd){
            button.draw_me();
        }

        std::string currencyText {};
        std::stringstream streamForCurrency {};
        streamForCurrency << std::fixed << "YOU WIN";
        currencyText = streamForCurrency.str();
        TextRenderer.SetColor(SimpleText::ForegroundBackground::TEXT_COLOR,SimpleText::Color::BLACK);
        TextRenderer.SetTextSize(SimpleText::FontSize::SIZE_48);
        TextRenderer.Label(currencyText.c_str(), (0.5)*_width, 300, SimpleText::CENTER);
    }
    // ---------------------------------------------------
    // CREDIT
    // ---------------------------------------------------
    if(myScreen._state == screen_state::INFO){
        // print_screen_state = "INFO";

        draw_background(screen_state::INFO);

        for(Button button : listOfButtonCredit){
            button.draw_me();
        }

        std::string currencyText {};
        std::stringstream streamForCurrency {};
        streamForCurrency << std::fixed << "Lucas Terrasson - Elvin Kauffmann - Fanny Ruiz";
        currencyText = streamForCurrency.str();
        TextRenderer.SetColor(SimpleText::ForegroundBackground::TEXT_COLOR,SimpleText::Color::BLACK);
        TextRenderer.SetTextSize(SimpleText::FontSize::SIZE_32);
        TextRenderer.Label(currencyText.c_str(), (0.5)*_width, 300, SimpleText::CENTER);
    }

    TextRenderer.Label(print_screen_state.c_str(), 100, 100, SimpleText::CENTER);

}