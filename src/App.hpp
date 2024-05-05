#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include "game/levels/level.hpp"



class App {
public:
    App();

    void setup();
    void update();

    double mouse_xpos;
    double mouse_ypos;

    double pos_mouse_x_abs;
    double pos_mouse_y_abs;

    double pos_tile_mouse_x;
    double pos_tile_mouse_y;
    
    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:
    void render();
    void draw_all_content();

    screen myScreen {};

    int _width {};
    int _height {};
    double _previousTime {};
    float _viewSize {};
    int _numberOfTiles {myScreen.nbrTileSide};
    
    float size {0.9};

    // Add your variables here
    GLuint _texture {};
    float _angle {};

    SimpleText TextRenderer {};
};