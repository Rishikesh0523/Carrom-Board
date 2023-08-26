#include "headers/MainMenu.h"
#include "headers/MainFrame.h"
#include "headers/GameModeWindow.h"
#include "headers/TextureManager.h"
#include "headers/AboutWindow.h"
#include "headers/music.h"
#include "headers/Leaderboard.h"

extern Initialization* MainWindow;
extern NewGameModes ModeWindow;
extern AboutSection AboutWindow;
extern Music* ClickSound;
extern Leaderboard LeaderboardWindow;


void MainMenu::render_developer_window() {

    developer_surface = IMG_Load("assets/logo.png");
    TextureManager::LTexture(MainWindow->renderer, developer_surface, developer_texture, NULL, NULL);
    SDL_Delay(2000);

}

void MainMenu::render_game_logo_window() {

    game_logo_surface = IMG_Load("assets/carrom.png");
    TextureManager::LTexture(MainWindow->renderer, game_logo_surface, game_logo_texture, NULL, NULL);
    SDL_Delay(2000);

}

void MainMenu::carrom_menu_background() {

    background_surface = IMG_Load("assets/carrom_background.png");
    TextureManager::LTexture(MainWindow->renderer, background_surface, background_texture, NULL, NULL);
    SDL_Delay(400);

}

void MainMenu::render_new_game_button() {

    if (new_game_button_state == true) {
        new_game_surface = IMG_Load("buttons/new_game_two.png");
        new_game_button_state = false;
    }
    else {
        new_game_surface = IMG_Load("buttons/new_game_one.png");
        new_game_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, new_game_surface, new_game_texture, NULL, &r1);
    SDL_Delay(100);

}

void MainMenu::render_leaderboard_button() {

    if (leaderboard_button_state == true) {
        leaderboard_surface = IMG_Load("buttons/leaderboard_two.png");
        leaderboard_button_state = false;
    }
    else {
        leaderboard_surface = IMG_Load("buttons/leaderboard_one.png");
        leaderboard_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, leaderboard_surface, leaderboard_texture, NULL, &r2);
    SDL_Delay(100);

}

void MainMenu::render_about_button() {

    if (about_button_state == true) {
        about_surface = IMG_Load("buttons/about_two.png");
        about_button_state = false;
    }
    else {
        about_surface = IMG_Load("buttons/about_one.png");
        about_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, about_surface, about_texture, NULL, &r3);
    SDL_Delay(100);

}

void MainMenu::render_exit_button() {

    if (exit_button_state == true) {
        exit_surface = IMG_Load("buttons/exit_two.png");
        exit_button_state = false;
    }
    else {
        exit_surface = IMG_Load("buttons/exit_one.png");
        exit_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, exit_surface, exit_texture, NULL, &r4);

}

void MainMenu::main_menu_window() {

    carrom_menu_background();
    render_new_game_button();
    render_leaderboard_button();
    render_about_button();
    render_exit_button();

}

void MainMenu::reset_button_states() {

    new_game_button_state = true;
    leaderboard_button_state = true;
    about_button_state = true;
    exit_button_state = true;

}

void MainMenu::handleMainMenuEvents(SDL_Event e) {

    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (SDL_BUTTON_LEFT == e.button.button) {

                if (x >= 720 + offsetX && x <= (720 + BUT_WIDTH + offsetX) && y >= 200 + offsetY && y <= (200 + BUT_HEIGHT + offsetY)) {
                    render_new_game_button();
                    ClickSound->PlayClickMusic();
                    currState = NEWGAMEMODES;
                    SDL_RenderClear(MainWindow->renderer);
                    carrom_menu_background();
                    ModeWindow.reset_mode_buttons_states();
                    ModeWindow.render_mode_buttons();

                }

                else if (x >= 720 + offsetX && x <= (720 + BUT_WIDTH + offsetX) && y >= 325 + offsetY && y <= (325 + BUT_HEIGHT + offsetY)) {
                    render_leaderboard_button();
                    ClickSound->PlayClickMusic();
                    SDL_RenderClear(MainWindow->renderer);
                    LeaderboardWindow.display_score_window();
                    SDL_Delay(5000);
                    SDL_RenderClear(MainWindow->renderer);
                    reset_button_states();
                    main_menu_window();
                }

                else if (x >= 770 + offsetX && x <= (770 + 200 + offsetX) && y >= 450 + offsetY && y <= (450 + BUT_HEIGHT + offsetY)) {
                    render_about_button();
                    ClickSound->PlayClickMusic();
                    currState = ABOUT;
                    SDL_RenderClear(MainWindow->renderer);
                    AboutWindow.reset_button_states();
                    AboutWindow.render_about_all();
                }

                else if (x >= 770 + offsetX && x <= (770 + 200 + offsetX) && y >= 575 + offsetY && y <= (575 + BUT_HEIGHT + offsetY)) {
                    render_exit_button();
                    ClickSound->PlayClickMusic();
                    MainWindow->is_running = false;
                }
            }
            break;

        default:
            break;
    }

}