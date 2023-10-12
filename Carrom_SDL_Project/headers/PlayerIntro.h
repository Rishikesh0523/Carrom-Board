#pragma once
#include <SDL.h>
#include<SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "MainMenu.h"

class PlayerIntro {
private:
	SDL_Texture* message_texture, * message_box_texture, * done_texture;
	SDL_Surface* message_surface, * message_box_surface, * done_surface;
	bool done_button_state = true;
	int offsetX = 150;
	int offsetY = 50;
	bool typing = true;

public:

	std::string textInputOne;
	std::string textInputTwo;
	std::string textInputThree;
	std::string textInputFour;

	SDL_Rect r11{ 260 + offsetX, 170 + offsetY, 400, 100 }, r12{ 300 + offsetX, 350 + offsetY, 300, 50};
	SDL_Rect r13{ 350 + offsetX, 550 + offsetY, 200, BUT_HEIGHT };

	void render_message();

	void render_message_box();

	void render_done_button();

	void reset_button_states();

	void render_intro_all();

	void handlePlayerIntroEvents(SDL_Event e);

};
