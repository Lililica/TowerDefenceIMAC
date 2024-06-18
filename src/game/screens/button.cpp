#include "button.hpp"

// Load button textures
img::Image buttonBEGIN {img::load(make_absolute_path("images/buttons/begin_button.png", true), 3, true)};
img::Image buttonPAUSE {img::load(make_absolute_path("images/buttons/pause_button.png", true), 3, true)};
img::Image buttonPLAY {img::load(make_absolute_path("images/buttons/play_button.png", true), 3, true)};
img::Image buttonRESTART {img::load(make_absolute_path("images/buttons/restart_button.png", true), 3, true)};
img::Image buttonQUIT {img::load(make_absolute_path("images/buttons/quit_button.png", true), 3, true)};
img::Image buttonCREDIT {img::load(make_absolute_path("images/buttons/credit_button.png", true), 3, true)};
img::Image typeTower1 {img::load(make_absolute_path("images/towers/tower1.png", true), 3, true)};
img::Image AnnuleTower {img::load(make_absolute_path("images/buttons/annule_tower.png", true), 3, true)};
img::Image typeTower2 {img::load(make_absolute_path("images/towers/tower2.png", true), 3, true)};
img::Image typeTower3 {img::load(make_absolute_path("images/towers/tower3.png", true), 3, true)};


void Button::draw_me(){
    glPushMatrix();
        glTranslatef(pos.first, pos.second, 0);
        glScalef(size.first,-size.second,1);
        draw_quad_with_texture(_texture);
    glPopMatrix();
}




void Button::set_stats_from_type() {
    switch (_type) {
        case BEGIN:
            _texture = loadTexture(buttonBEGIN);
            break;
        case CONTINU:
            _texture = loadTexture(buttonBEGIN);
            break;
        case PAUSE:
            _texture = loadTexture(buttonPAUSE);
            break;
        case PLAY:
            _texture = loadTexture(buttonPLAY);
            break;
        case RESTART:
            _texture = loadTexture(buttonRESTART);
            break;
        case QUIT :
            _texture = loadTexture(buttonQUIT);
            break;
        case EXIT_TO_MENU :
            _texture = loadTexture(buttonQUIT);
            break;
        case CREDIT:
            _texture = loadTexture(buttonCREDIT);
            break;
        case TOWER_1:
            _texture = loadTexture(typeTower1);
            break;
        case ANNULER_TOWER:
            _texture = loadTexture(AnnuleTower);
            break;
        case TOWER_2:
            _texture = loadTexture(typeTower2);
            break;
        case TOWER_3:
            _texture = loadTexture(typeTower3);
            break;
        default:
            _texture = loadTexture(buttonBEGIN);
    }
}


