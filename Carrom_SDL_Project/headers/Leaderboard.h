#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Leaderboard {
private:
	SDL_Surface* surface;
	SDL_Texture* texture;

public:
	void display_score_window();
};
