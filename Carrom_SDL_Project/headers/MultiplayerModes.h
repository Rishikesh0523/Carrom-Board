#pragma once
# include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "MainMenu.h"


class MultiPlayerModes {

	private:
		bool twoplayer_button_state = true;
		bool fourplayer_button_state = true;
		bool back_button_state = true;

		int offsetX = 0;
		int offsetY = 0;

		SDL_Texture* twoplayer_texture, * fourplayer_texture, * back_texture;
		SDL_Surface* twoplayer_surface, * fourplayer_surface, * back_surface;

	public:

		SDL_Rect r18{820+offsetX, 350+offsetY, BUT_WIDTH, BUT_HEIGHT}, r19{820+offsetX, 475+offsetY, BUT_WIDTH, BUT_HEIGHT};
		SDL_Rect r20{870+offsetX, 600+offsetY, 200, BUT_HEIGHT};

		void render_twoplayer_button();

		void render_fourplayer_button();

		void render_back_button();

		void render_multiplayermode_buttons();

		void reset_button_states();

		void handleMultiPlayerModesEvents(SDL_Event e);
		
};
