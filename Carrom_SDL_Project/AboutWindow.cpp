#include "headers/AboutWindow.h"
#include "headers/TextureManager.h"
#include "headers/MainFrame.h"
#include "headers/MainMenu.h"
#include "headers/fonts.h"
#include "headers/music.h"

extern Initialization* MainWindow;
extern MainMenu MenuWindow;
extern Music* ClickSound;

void AboutSection::render_about_window() {
	
	about_win_surface = IMG_Load("assets/background.png");
	TextureManager::LTexture(MainWindow->renderer, about_win_surface, about_win_texture, NULL, NULL);

}

void AboutSection::render_message() {

    FontManager::LFont(MainWindow->renderer, message_surface, message_texture, MainWindow->fontType, "Carrom King v 0.1.1", { 255, 255, 255 }, &r5);

}

void AboutSection::render_message_one() {

    FontManager::LFont(MainWindow->renderer, message_one_surface, message_one_texture, MainWindow->fontType, "This game is brought to you by", { 218, 165, 32 }, &r5_one);

}

void AboutSection::render_message_two() {

    FontManager::LFont(MainWindow->renderer, message_two_surface, message_two_texture, MainWindow->fontType, "CodeMasters aka. Rishikesh Paudel, Pratik ", { 218, 165, 32 }, &r5_two);

}

void AboutSection::render_message_three() {

    FontManager::LFont(MainWindow->renderer, message_three_surface, message_three_texture, MainWindow->fontType, "Adhikari and Prabesh Bashyal.", { 218, 165, 32 }, &r5_three);

}
void AboutSection::render_close_button() {

    if (close_button_state == true) {
        close_surface = IMG_Load("buttons/close_two.png");
        close_button_state = false;
    }
    else {
        close_surface = IMG_Load("buttons/close_one.png");
        close_button_state = true;
    }

    TextureManager::LTexture(MainWindow->renderer, close_surface, close_texture, NULL, &r6);

}

void AboutSection::render_about_all() {

    render_about_window();
    render_message();
    render_message_one();
    render_message_two();
    render_message_three();
    render_close_button();

}

void AboutSection::reset_button_states() {
    
    close_button_state = true;
   
}

void AboutSection::handleAboutWindowEvents(SDL_Event e) {

    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (SDL_BUTTON_LEFT == e.button.button) {
                if (x >= 440 + offsetX && x <= 640 + offsetX && y >= 600 + offsetY && y <= 600 + BUT_HEIGHT + offsetY) {

                    render_close_button();
                    ClickSound->PlayClickMusic();
                    SDL_RenderClear(MainWindow->renderer);
                    currState = MAINMENU;
                    MenuWindow.reset_button_states();
                    MenuWindow.main_menu_window();
                }
            }
            break;
        default:
            break;
    }

}