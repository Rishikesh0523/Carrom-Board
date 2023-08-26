#include "headers/TwoPlayerIntro.h"
#include "headers/MainFrame.h"
#include "headers/MainMenu.h"
#include "headers/TextureManager.h"
#include "headers/music.h"
#include "headers/fonts.h"
#include "headers/SinglePlayerGame.h"
#include "headers/AboutWindow.h"
#include "headers/TwoPlayerGame.h"

extern Initialization* MainWindow;
extern MainMenu MenuWindow;
extern Music* ClickSound;
extern SinglePlayerGame SinglePlayerGameWindow;
extern TwoPlayerInfo TwoInfo;
extern AboutSection AboutWindow;
extern TwoPlayerGame TwoPlayerGameWindow;



void TwoPlayerIntro::render_message() {

	FontManager::LFont(MainWindow->renderer, message_surface, message_texture, MainWindow->fontType, "Enter your name ", { 218, 165, 32 }, &r21);

}

void TwoPlayerIntro::render_message_box() {

	SDL_RenderClear(MainWindow->renderer);
	AboutWindow.render_about_window();
	reset_button_states();
	render_intro_all();
	FontManager::LFont(MainWindow->renderer, message_box_surface, message_box_texture, MainWindow->fontType, textInputOne.c_str(), { 255, 255, 255 }, &r22);

}

void TwoPlayerIntro::render_done_button() {

	if (done_button_state == true) {
		done_surface = IMG_Load("buttons/done_two.png");
		done_button_state = false;
	}
	else {
		done_surface = IMG_Load("buttons/done_one.png");
		done_button_state = true;
	}

	TextureManager::LTexture(MainWindow->renderer, done_surface, done_texture, NULL, &r23);

}

void TwoPlayerIntro::render_intro_all() {

	render_message();
	render_done_button();

}

void TwoPlayerIntro::reset_button_states() {

	done_button_state = true;

}



void TwoPlayerIntro::handleTwoPlayerIntroEvents(SDL_Event e) {
	int n = 1;
	switch (e.type) {

		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);

			if (x >= 370 + offsetX && x <= 370 + 200 + offsetX && y >= 550 + offsetY && y <= 550 + offsetY + BUT_HEIGHT) {
				render_done_button();
				ClickSound->PlayClickMusic();
				std::cout << "Player 1 :  " << textInputOne << std::endl;

			}

			if (x >= 370 + offsetX && x <= 370 + 200 + offsetX && y >= 550 + offsetY && y <= 550 + offsetY + BUT_HEIGHT) {
				render_done_button();
				ClickSound->PlayClickMusic();
				std::cout << "Player 2 :  " << textInputTwo << std::endl;
				SDL_Delay(2000);
				currState = SINGLEPLAYERGAME;
				SDL_RenderClear(MainWindow->renderer);
				SinglePlayerGameWindow.render_singleplayer_window();
				SinglePlayerGameWindow.reset_button_states();
				SinglePlayerGameWindow.render_back_button();
				TwoInfo.displayPlayerName();
				TwoInfo.displayScoreName();
				TwoInfo.displayPlayerOneName(textInputOne+ " 1");
				TwoInfo.displayPlayerTwoName(textInputTwo+ " 2");

				ClickSound->PauseBackgroundMusic();
				SDL_Delay(2000);
				const char* command = "start cmd /k \"D: && cd \"D:/Carrom_Board_Final/dependencies\" && finale\"";
				int returnValue = system(command);

			}
			break;
		

		case SDL_KEYDOWN:
			if (typing) {
				if (e.key.keysym.sym == SDLK_RETURN) {
					typing = false;
				}

				else if (e.key.keysym.sym == SDLK_BACKSPACE && textInputOne.length() > 0) {
					textInputOne.pop_back();
					render_message_box();
				}
			}

			if (typing) {
				if (e.key.keysym.sym == SDLK_RETURN) {
					typing = false;
				}

				else if (e.key.keysym.sym == SDLK_BACKSPACE && textInputTwo.length() > 0) {
					textInputTwo.pop_back();
					render_message_box();
				}
			}
			break;

		case SDL_TEXTINPUT:
			if (typing)
			{
				SDL_StartTextInput();
				textInputOne += e.text.text;
				render_message_box();
			}
			if (typing)
			{
				SDL_StartTextInput();
				textInputTwo += e.text.text;
				render_message_box();
			}
			break;

		default:
			break;

	}

}
