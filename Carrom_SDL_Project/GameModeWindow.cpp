#include "headers/GameModeWindow.h"
#include "headers/MainFrame.h"
#include "headers/TextureManager.h"
#include "headers/MainMenu.h"
#include "headers/music.h"
#include "headers/OverLANModes.h"
#include "headers/PlayerIntro.h"
#include "headers/MultiplayerModes.h"

extern Initialization* MainWindow;
extern MainMenu MenuWindow;
extern Music* ClickSound;
extern OverLANModes LANModeWindow;
extern AboutSection AboutWindow;
extern PlayerIntro IntroWindow;
extern MultiPlayerModes MultiPlayerModeWindow;

void NewGameModes::render_singleplayer_button() {

    if (single_player_button_state == true) {
        single_player_surface = IMG_Load("buttons/single_player_two.png");
        single_player_button_state = false;
    }

    else {
        single_player_surface = IMG_Load("buttons/single_player_one.png");
        single_player_button_state = true;
    }

	TextureManager::LTexture(MainWindow->renderer, single_player_surface, single_player_texture, NULL, &r1);
    SDL_Delay(100);
}

void NewGameModes::render_multiplayer_button() {

    if (multiplayer_button_state == true) {
        multiplayer_surface = IMG_Load("buttons/multiplayer_two.png");
        multiplayer_button_state = false;
    }
    else {
        multiplayer_surface = IMG_Load("buttons/multiplayer_one.png");
        multiplayer_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, multiplayer_surface, multiplayer_texture, NULL, &r2);
    SDL_Delay(100);

}

void NewGameModes::render_overlan_button() {

    if (over_LAN_button_state == true) {
        over_LAN_surface = IMG_Load("buttons/over_LAN_two.png");
        over_LAN_button_state = false;
    }
    else {
        over_LAN_surface = IMG_Load("buttons/over_LAN_one.png");
        over_LAN_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, over_LAN_surface, over_LAN_texture, NULL, &r7);
    SDL_Delay(100);

}

void NewGameModes::render_back_button() {

    if (back_button_state == true) {
        back_surface = IMG_Load("buttons/back_two.png");
        back_button_state = false;
    }
    else {
        back_surface = IMG_Load("buttons/back_one.png");
        back_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, back_surface, back_texture, NULL, &r4);

}

void NewGameModes::render_mode_buttons() {

    render_singleplayer_button();
    render_multiplayer_button();
    render_overlan_button();
    render_back_button();

}

void NewGameModes::reset_mode_buttons_states() {

    single_player_button_state = true;
    multiplayer_button_state = true;
    over_LAN_button_state = true;
    back_button_state = true;

}

void NewGameModes::handleNewGameModeEvents(SDL_Event e) {

    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (SDL_BUTTON_LEFT == e.button.button) {

                if (x >= 720 + offsetX && x <= (720 + BUT_WIDTH + offsetX) && y >= 200 + offsetY && y <= (200 + BUT_HEIGHT + offsetY)) {
                    render_singleplayer_button();
                    ClickSound->PlayClickMusic();
                    currState = SINGLEPLAYERINTRO;
                    SDL_RenderClear(MainWindow->renderer);
                    AboutWindow.render_about_window();
                    IntroWindow.reset_button_states();
                    IntroWindow.render_intro_all();
                    
                }

                else if (x >= 720 + offsetX && x <= (720 + BUT_WIDTH + offsetX) && y >= 325 + offsetY && y <= (325 + BUT_HEIGHT + offsetY)) {
                    render_multiplayer_button();
                    ClickSound->PlayClickMusic();
                    currState = MULTIPLAYERGAMEMODES;
                    SDL_RenderClear(MainWindow->renderer);
                    MenuWindow.carrom_menu_background();
                    MultiPlayerModeWindow.reset_button_states();
                    MultiPlayerModeWindow.render_multiplayermode_buttons();
                    
                }

                else if (x >= 745 + offsetX && x <= (995 + offsetX) && y >= 450 + offsetY && y <= (450 + BUT_HEIGHT + offsetY)) {
                    render_overlan_button();
                    ClickSound->PlayClickMusic();
                    currState = OVERLANMODES;
                    SDL_RenderClear(MainWindow->renderer);
                    MenuWindow.carrom_menu_background();
                    LANModeWindow.reset_overlanmodes_button_state();
                    LANModeWindow.render_overlanmodes_buttons();

                }

                else if (x >= 770 + offsetX && x <= 970 + offsetX && y >= 575 + offsetY && 575 + BUT_HEIGHT + offsetY) {
                    render_back_button();
                    ClickSound->PlayClickMusic();
                    currState = MAINMENU;
                    SDL_RenderClear(MainWindow->renderer);
                    MenuWindow.reset_button_states();
                    MenuWindow.main_menu_window();
                    
                }
            }
            break;

        default:
            break;
    }

}
