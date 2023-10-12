#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "MainMenu.h"
#include "AboutWindow.h"
#include "MainFrame.h"

class OverLANModes {

	private:

		bool host_button_state = true;
		bool join_button_state = true;
		bool back_button_state = true;

		SDL_Texture* join_texture, * host_texture, * back_texture, *coming_texture;
		SDL_Surface* join_surface, * host_surface, * back_surface, *coming_surface;
		int offsetX = 100;
		int offsetY = 0;

	public:

		SDL_Rect r8{ 820 + offsetX, 350 + offsetY, 200, BUT_HEIGHT }, r9{820 + offsetX, 475+offsetY, 200, BUT_HEIGHT};
		SDL_Rect r10{ 820 + offsetX, 600 + offsetY, 200, BUT_HEIGHT };

		SDL_Rect fontrenderrect{WIN_WIDTH/2-200, WIN_HEIGHT/2-150, 400, 200};

		void render_host_button();

		void render_join_button();

		void render_back_button();

		void render_overlanmodes_buttons();

		void reset_overlanmodes_button_state();

		void handleOverLANModesEvents(SDL_Event e);

		void coming_soon_window();

};
