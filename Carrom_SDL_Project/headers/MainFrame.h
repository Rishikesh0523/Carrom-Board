#pragma once
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

enum windowStates {
	MAINMENU,
	NEWGAMEMODES,
	LEADERBOARD,
	ABOUT,
	SINGLEPLAYERINTRO,
	SINGLEPLAYERGAME,
	MULTIPLAYERGAMEMODES,
	TWOPLAYERINTRO,
	TWOPLAYERGAME,
	OVERLANMODES,
	OVERLANGAME

};

const int WIN_WIDTH = 1180, WIN_HEIGHT = 950;
const int CARROM_PIECE_SIZE = 42;
const int STRIKER_PIECE_SIZE = 50;

const int GAME_BORDER = 53;
const int POCKET_WIDTH = 45;
const int pieceSize = CARROM_PIECE_SIZE;
const int centerOffset = (WIN_HEIGHT - pieceSize) / 2;

extern windowStates currState;

class Initialization {

	private:

		int flags = 0;

	public:

		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* fontType;

		bool is_running = true;

		Initialization() {}
		~Initialization() {}

		void windowInit(const char* title, int x_pos, int y_pos, int p_w, int p_h, bool fullscreen);

		bool runningState() { return is_running; }

		void handleMainEvent(SDL_Event e);
		
		void clean();
};	
