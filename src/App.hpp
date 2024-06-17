#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include "game/screens/screen.hpp"
#include "game/entities/entity.hpp"
#include "game/screens/button.hpp"
#include <utility>
#include "game/entities/entity.hpp"
#include "game/draws/draw.hpp"
#include <img/img.hpp>


class App {
public:
    App();

    void setup();
    void update();

    std::pair<double, double> mouse_pos;
    
    std::pair<double, double> pos_mouse_abs;

    std::pair<double, double> pos_tile_mouse;

    
    // Convert coordonnées

    std::pair<double, double> screen_px_to_squareScreen_px(std::pair<double, double> pos);
    std::pair<double, double> squareScreen_px_to_squareScreen_abs(std::pair<double, double> pos);
    std::pair<double, double> squareScreen_abs_to_SquareScreen_tiles(std::pair<double, double> pos);
    

    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:
    void render();
    void draw_all_content();
    void draw_background(screen_state const& Screen);

    Screen myScreen {};

    int _width {};
    int _height {};
    double _previousTime {};
    float _viewSize {};
    int _numberOfTiles {myScreen.nbrTileSide};
    
    float size {0.9};

    // Add your variables here
    GLuint _texture {};
    GLuint _enemyTextureTest {};
    float _angle {};

    SimpleText TextRenderer {};

    std::vector<std::pair<screen_state,img::Image>> listOfBackgroundTextures;
    
    std::vector<Button> listOfButton;


    std::vector<Tower> listOfTower;

    std::vector<Enemy> listOfEnemy;
    void removeDeadEnemies();

};