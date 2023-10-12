#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "MainMenu.h"
#include "OverLANModes.h"


class AboutSection {

	private:
		bool close_button_state = true;
		SDL_Surface* about_win_surface, * close_surface, * message_surface, * message_one_surface, * message_two_surface, * message_three_surface;
		SDL_Texture* about_win_texture, * close_texture, * message_texture, * message_one_texture, * message_two_texture, * message_three_texture;

		int offsetX = 60;
		int offsetY = 100;

	public:
		SDL_Rect r5{ 350 + offsetX, 70 + offsetY, 400, 70 };
		SDL_Rect r5_one{ 290 + offsetX, 210 + offsetY, 500, 70 };
		SDL_Rect r5_two{ 210 + offsetX, 280 + offsetY, 700, 70 };
		SDL_Rect r5_three{ 290 + offsetX, 350 + offsetY, 500, 70 };
		SDL_Rect r6{ 440 + offsetX, 600 + offsetY, 200, BUT_HEIGHT };
		

		void render_about_window();

		void render_message();

		void render_message_one();

		void render_message_two();

		void render_message_three();

		void render_close_button();

		void render_about_all();

		void reset_button_states();

		void handleAboutWindowEvents(SDL_Event e);

};
