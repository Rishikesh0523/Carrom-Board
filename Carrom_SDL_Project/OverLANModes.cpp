#include "headers/music.h"
#include "headers/OverLANModes.h"
#include "headers/TextureManager.h"
#include "headers/GameModeWindow.h"
#include "headers/fonts.h"
#include "headers/AboutWindow.h"

extern Initialization* MainWindow;
extern Music* ClickSound;
extern NewGameModes ModeWindow;
extern MainMenu MenuWindow;
extern AboutSection AboutWindow;

void OverLANModes::render_host_button() {

    if (host_button_state == true) {
        host_surface = IMG_Load("buttons/host_two.png");
        host_button_state = false;
    }
    else {
        host_surface = IMG_Load("buttons/host_one.png");
        host_button_state = true;
    }

	TextureManager::LTexture(MainWindow->renderer, host_surface, host_texture, NULL, &r8);
    SDL_Delay(100);

}

void OverLANModes::render_join_button() {

    if (join_button_state == true) {
        join_surface = IMG_Load("buttons/join_two.png");
        join_button_state = false;
    }
    else {
        join_surface = IMG_Load("buttons/join_one.png");
        join_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, join_surface, join_texture, NULL, &r9);
    SDL_Delay(100);

}

void OverLANModes::render_back_button() {

    if (back_button_state == true) {
        back_surface = IMG_Load("buttons/back_two.png");
        back_button_state = false;
    }
    else {
        back_surface = IMG_Load("buttons/back_one.png");
        back_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, back_surface, back_texture, NULL, &r10);

}

void OverLANModes::render_overlanmodes_buttons() {

    render_host_button();
    render_join_button();
    render_back_button();

}

void OverLANModes::reset_overlanmodes_button_state() {

    host_button_state = true;
    join_button_state = true;
    back_button_state = true;

}

void OverLANModes::coming_soon_window() {

    SDL_RenderClear(MainWindow->renderer);
    AboutWindow.render_about_window();
    FontManager::LFont(MainWindow->renderer, coming_surface, coming_texture, MainWindow->fontType, "Coming Soon", { 218, 165, 32 }, &fontrenderrect);

}

void OverLANModes::handleOverLANModesEvents(SDL_Event e) {

    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (SDL_BUTTON_LEFT == e.button.button) {
                if (x >= 820 + offsetX && x <= 820 + 200 + offsetX && y >= 350 + offsetY && y <= 350 + BUT_HEIGHT + offsetY) {
                    render_host_button();
                    ClickSound->PlayClickMusic();
                    coming_soon_window();
                    SDL_Delay(3000);
                    SDL_RenderClear(MainWindow->renderer);
                    currState = OVERLANMODES;
                    MenuWindow.carrom_menu_background();
                    reset_overlanmodes_button_state();
                    render_overlanmodes_buttons();
                    
                }

                else if (x >= 820 + offsetX && x <= 820 + 200 + offsetX && y >= 475 + offsetY && y <= 475 + BUT_HEIGHT + offsetY) {
                    render_join_button();
                    ClickSound->PlayClickMusic();
                    coming_soon_window();
                    SDL_Delay(3000);
                    SDL_RenderClear(MainWindow->renderer);
                    currState = OVERLANMODES;
                    MenuWindow.carrom_menu_background();
                    reset_overlanmodes_button_state();
                    render_overlanmodes_buttons();

                }

                else if (x >= 820 + offsetX && x <= 820 + 200 + offsetX && y >= 600 + offsetY && y <= 600 + BUT_HEIGHT + offsetY) {
                    render_back_button();
                    ClickSound->PlayClickMusic();
                    currState = NEWGAMEMODES;
                    SDL_RenderClear(MainWindow->renderer);
                    MenuWindow.carrom_menu_background();
                    ModeWindow.reset_mode_buttons_states();
                    ModeWindow.render_mode_buttons();

                }
            }
            break;

        default:
            break;

    }

}
