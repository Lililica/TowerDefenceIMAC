#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include "game/screens/screen.hpp"
#include "game/entities/entity.hpp"
#include "game/screens/button.hpp"
#include <utility>
#include "game/entities/entity.hpp"
#include "game/draws/draw.hpp"
#include "img/img.hpp"
#include <string>
#include <map>

class App {
public:
    App();

    void setup();
    void update();
    

    std::pair<double, double> mouse_pos;
    
    std::pair<double, double> pos_mouse_abs;

    std::pair<double, double> pos_tile_mouse;

    double currentTime;
    
    // Convert coordonnées

    std::pair<double, double> screen_px_to_squareScreen_px(std::pair<double, double> pos);
    std::pair<double, double> squareScreen_px_to_squareScreen_abs(std::pair<double, double> pos);
    std::pair<double, double> squareScreen_abs_to_SquareScreen_tiles(std::pair<double, double> pos);

    double transform_mouse_pos_tile_to_case_index(std::pair<double, double> pos);
    bool isFreeToBuild();

    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

    bool windowsShouldClose {false};

private:
    void render();
    void draw_all_content();
    void draw_background(screen_state const& Screen);

    Screen myScreen {};

    int globalLife {3};

    int _width {};
    int _height {};
    double _previousTime {};
    float _viewSize {};
    int _numberOfTiles {myScreen.nbrTileSide};
    double tileSize {};
    
    float size {0.9};

    bool vague1 {false};
    bool vague2 {false};
    bool vague3 {false};
    bool vague4 {false};
    bool firstStart {false};
    double timeSinceStart {};
    
    bool isPaused = false;
    double pauseStartTime = 0;
    double pausedTime = 0;

    // Add your variables here
    GLuint _texture {};
    GLuint _enemyTextureTest {};
    float _angle {};

    SimpleText TextRenderer {};

    std::vector<std::pair<screen_state,img::Image>> listOfBackgroundTextures;
    
    std::vector<Button> listOfButtonMenu;

    std::vector<Button> listOfButtonPause;

    std::vector<Button> listOfButtonTowerLevel;

    std::vector<Button> listOfButtonEnd;
    std::vector<Button> listOfButtonCredit;

    double delayForTowerPlacement;
    int idTower {0};
    std::vector<Tower> listOfTower;
    Price price;

    std::vector<Enemy> listOfEnemy;
    std::vector<std::vector<GLuint>> listOfEnnemyTexture;
    int itAnimation {0};
    double intervalForAnim {0};
  void remove_enemy(int id);

    std::vector<Case> listOfNodes {Case{0, START, false, std::pair<double,double>{-1.,1.}}, 
                            Case{200, PATH, false, std::pair<double,double>{-1,0}},
                            Case{210, PATH, false, std::pair<double,double>{0,0}},
                            Case{110, PATH, false, std::pair<double,double>{0,0.5}},
                            Case{115, PATH, false, std::pair<double,double>{0.5,0.5}},
                            Case{315, PATH, false, std::pair<double,double>{0.5,-0.5}},
                            Case{319, PATH, false, std::pair<double,double>{1. - (2./_numberOfTiles),-0.5}},
                            Case{399, END, false, std::pair<double,double>{1. - (2./_numberOfTiles), -1. + (2./_numberOfTiles)}}
                            };

    // std::vector<Case> listOfCase;

    std::vector<img::Image> listOfCaseImg;    

    std::vector<GLuint> listOfCaseTexture;  

    // void remplir_listOfCase();

    double delayForAllButton {};

    void removeDeadEnemies();
    Enemy* findEnemyFromList(int wantedId);
};