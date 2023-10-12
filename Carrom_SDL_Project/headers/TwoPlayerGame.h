#pragma once

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>
#include "MainFrame.h"
#include "MainMenu.h"

extern Initialization* MainWindow;


class TwoPlayerGame {

private:
	bool back_button_state = true;
	SDL_Surface* background_surface, * back_surface;
	SDL_Texture* background_texture, * back_texture;

public:
	SDL_Rect r20{ WIN_WIDTH / 2 - 100, 750, 200, BUT_HEIGHT };

	void background();

	void render_twoplayer_window();

	void render_back_button();

	void reset_button_states();

	void handleTwoPlayerGameEvents(SDL_Event e);


};


struct TwoPlayerInfo {

	SDL_Texture* score_texture, * playername_texture, * player1_texture, * player2_texture;
	SDL_Surface* score_surface, * playername_surface, * player1_surface, * player2_surface;

	SDL_Texture* scoreone_texture, * scoretwo_texture;
	SDL_Surface* scoreone_surface, * scoretwo_surface;

	SDL_Rect playerOne{ WIN_WIDTH / 3 - 200, 300, 300, 100 };


	SDL_Rect playerTwo{ WIN_WIDTH / 3 - 200, 500, 300, 100 };


	SDL_Rect playername{ WIN_WIDTH / 3 - 200, 200, 400, 100 };

	SDL_Rect scorename{ WIN_WIDTH - 400, 200, 200, 100 };

	SDL_Rect scoreOne{ 4 * WIN_WIDTH / 3 - 200, 300, 300, 100 };

	SDL_Rect scoreTwo{ 4 * WIN_WIDTH / 3 - 200, 300, 300, 100 };

	SDL_Rect r15{ 950 + 10, 550, 200, 50 };

	//SDL_Rect r16{ 950 + 50, 450, 100, 50 };

	int score;

	void displayPlayerName(std::string player = "Player Name");

	void displayScoreName(std::string score = "Score");

	void displayPlayerOneName(std::string playername);

	void displayPlayerTwoName(std::string playername);

	void displayPlayerScore(int playerscore);

};

