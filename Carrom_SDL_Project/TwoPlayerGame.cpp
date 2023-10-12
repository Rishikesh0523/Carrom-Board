#include "headers/TwoPlayerGame.h"
#include "headers/MainFrame.h"
#include "headers/music.h"
#include "headers/GameModeWindow.h"
#include "headers/TwoPlayerIntro.h"
#include "headers/TextureManager.h"
#include "headers/fonts.h"

extern Initialization* MainWindow;
extern Music* BackMusic;
extern Music* ClickSound;
extern NewGameModes ModeWindow;
extern MainMenu MenuWindow;
extern TwoPlayerIntro TwoPlayerIntroWindow;


void TwoPlayerGame::background() {

	background_surface = IMG_Load("assets/background.png");

	TextureManager::LTexture(MainWindow->renderer, background_surface, background_texture, NULL, NULL);

}


void TwoPlayerGame::render_back_button() {

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

void TwoPlayerGame::reset_button_states() {

	back_button_state = true;

}

void TwoPlayerGame::render_twoplayer_window() {

	background();
	render_back_button();

}

void TwoPlayerGame::handleTwoPlayerGameEvents(SDL_Event e) {

	switch (e.type) {
	case SDL_MOUSEBUTTONDOWN:
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x >= WIN_WIDTH / 2 - 100 && x <= WIN_WIDTH / 2 - 100 + 200 && y >= 750 && y <= 750 + BUT_HEIGHT) {

			if (e.button.button == SDL_BUTTON_LEFT) {
				render_back_button();
				ClickSound->PlayClickMusic();
				SDL_RenderClear(MainWindow->renderer);
				TwoPlayerIntroWindow.textInputOne = "";

				currState = MAINMENU;
				SDL_RenderClear(MainWindow->renderer);
				BackMusic->PlayBackgroundMusic(-1);
				MenuWindow.carrom_menu_background();
				MenuWindow.reset_button_states();
				MenuWindow.main_menu_window();

			}
		}
		break;

	default:
		break;

	}

}



void TwoPlayerInfo::displayPlayerName(std::string player) {

	FontManager::LFont(MainWindow->renderer, playername_surface, playername_texture, MainWindow->fontType, player, { 255, 255, 255 }, &playername);

}

void TwoPlayerInfo::displayScoreName(std::string score) {

	FontManager::LFont(MainWindow->renderer, score_surface, score_texture, MainWindow->fontType, score, { 255, 255, 255 }, &scorename);

}


void TwoPlayerInfo::displayPlayerOneName(std::string playername) {

	FontManager::LFont(MainWindow->renderer, player1_surface, player1_texture, MainWindow->fontType, playername, { 218, 165, 32 }, &playerOne);

}

void TwoPlayerInfo::displayPlayerTwoName(std::string playername) {

	FontManager::LFont(MainWindow->renderer, player2_surface, player2_texture, MainWindow->fontType, playername, { 218, 165, 32 }, &playerTwo);

}

void TwoPlayerInfo::displayPlayerScore(int playerscore = 0) {

	/*std::string playersc = std::to_string(playerscore);
	FontManager::LFont(MainWindow->renderer, score_surface, score_texture, MainWindow->fontType, playerscore, { 255, 255, 255 }, &r16);*/

}