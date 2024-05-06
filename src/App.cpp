#include "App.hpp"
#include "game/draws/draw.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

App::App() : _previousTime(0.0), _viewSize(2.0) {
   // load what needs to be loaded here (for example textures)

    img::Image test {img::load(make_absolute_path("images/level.png", true), 3, true)};
    
    _texture = loadTexture(test);
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
}

void App::update() {

    const double currentTime { glfwGetTime() };
    const double elapsedTime { currentTime - _previousTime};
    _previousTime = currentTime;

    _angle += 10.0f * elapsedTime;

    

    mouse_xpos = (mouse_xpos - (_width - _height)/2)*size - (_height -(_height*size))/2;
    mouse_ypos = mouse_ypos*size - (_height -(_height*size))/2;

    pos_mouse_x_abs = (mouse_xpos*2)/(((_height - (_height -(_height*size))/2))*size - (_height -(_height*size))/2) - 1.f;
    pos_mouse_y_abs =  -(mouse_ypos*2)/(((_height - (_height -(_height*size))/2))*size - (_height -(_height*size))/2) + 1.f;

    pos_tile_mouse_x = (int((pos_mouse_x_abs + 1)*_numberOfTiles/2))*(2/float(_numberOfTiles)) - 1. + 2/float(_numberOfTiles);
    pos_tile_mouse_y = -(_numberOfTiles - int((pos_mouse_y_abs + 1)*_numberOfTiles/2) - 1)*(2/float(_numberOfTiles)) + 1. - 2/float(_numberOfTiles);

    render();
}

void App::render() {
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glScalef(size, size, 1);
        draw_all_content();
    glPopMatrix();



    TextRenderer.Render();
}

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/) {
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/) {
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

