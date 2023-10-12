#include "headers/MultiplayerModes.h"
#include "headers/MainFrame.h"
#include "headers/TextureManager.h"
#include "headers/music.h"
#include "headers/GameModeWindow.h"
#include "headers/OverLANModes.h"
#include "headers/AboutWindow.h"
#include "headers/TwoPlayerIntro.h"

extern Initialization* MainWindow;
extern Music* ClickSound;
extern MainMenu MenuWindow;
extern NewGameModes ModeWindow;
extern OverLANModes LANModeWindow;
extern AboutSection AboutWindow;
extern TwoPlayerIntro TwoPlayerIntroWindow;

void MultiPlayerModes::render_twoplayer_button() {

	if (twoplayer_button_state == true) {
		twoplayer_surface = IMG_Load("buttons/twoplayer_two.png");
		twoplayer_button_state = false;
	}
	else {
		twoplayer_surface = IMG_Load("buttons/twoplayer_one.png");
		twoplayer_button_state = true;
	}

	TextureManager::LTexture(MainWindow->renderer, twoplayer_surface, twoplayer_texture, NULL, &r18);
	SDL_Delay(100);

}

void MultiPlayerModes::render_fourplayer_button() {

	if (fourplayer_button_state == true) {
		fourplayer_surface = IMG_Load("buttons/fourplayer_two.png");
		fourplayer_button_state = false;
	}
	else {
		fourplayer_surface = IMG_Load("buttons/fourplayer_one.png");
		fourplayer_button_state = true;
	}

	TextureManager::LTexture(MainWindow->renderer, fourplayer_surface, fourplayer_texture, NULL, &r19);
	SDL_Delay(100);

}

void MultiPlayerModes::render_back_button() {

	if (back_button_state == true) {
		back_surface = IMG_Load("buttons/back_two.png");
		back_button_state = false;
	}
	else {
		back_surface = IMG_Load("buttons/back_one.png");
		back_button_state = true;
	}

	TextureManager::LTexture(MainWindow->renderer, back_surface, back_texture, NULL, &r20);

}

void MultiPlayerModes::render_multiplayermode_buttons() {

	render_twoplayer_button();
	render_fourplayer_button();
	render_back_button();

}

void MultiPlayerModes::reset_button_states() {

	back_button_state = true;
	twoplayer_button_state = true;
	fourplayer_button_state = true;

}

void MultiPlayerModes::handleMultiPlayerModesEvents(SDL_Event e) {

	switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x >= 820 + offsetX && x <= 820 + BUT_WIDTH + offsetY && y >= 350 + offsetY && y <= 350 + BUT_HEIGHT + offsetY) {
					render_twoplayer_button();
					ClickSound->PlayClickMusic();
					currState = TWOPLAYERINTRO;
					SDL_RenderClear(MainWindow->renderer);
					AboutWindow.render_about_window();
					TwoPlayerIntroWindow.reset_button_states();
					TwoPlayerIntroWindow.render_intro_all();
				}

				else if (x >= 820 + offsetX && x <= 820 + BUT_WIDTH + offsetY && y >= 475 + offsetY && y <= 475 + BUT_HEIGHT + offsetY) {
					render_fourplayer_button();
					ClickSound->PlayClickMusic();
					LANModeWindow.coming_soon_window();
					SDL_Delay(3000);
					SDL_RenderClear(MainWindow->renderer);
					currState = MULTIPLAYERGAMEMODES;
					MenuWindow.carrom_menu_background();
					reset_button_states();
					render_multiplayermode_buttons();
				}
				
				else if (x >= 870 + offsetX && x <= 870 + 200 + offsetX && y >= 600 + offsetY && 600 + BUT_HEIGHT + offsetY) {
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