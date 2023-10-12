#pragma once
#include<SDL.h>
#include<SDL_image.h>

const int BUT_WIDTH = 300, BUT_HEIGHT = 100;

class MainMenu {

	private:
        
        bool new_game_button_state = true;
        bool leaderboard_button_state = true;
        bool about_button_state = true;
        bool exit_button_state = true;
        int offsetX = 100;
        int offsetY = 100;

		SDL_Surface* developer_surface, * game_logo_surface, * background_surface, * new_game_surface, * leaderboard_surface, * about_surface, * exit_surface;
		SDL_Texture* developer_texture, * game_logo_texture, * background_texture, * new_game_texture, * leaderboard_texture, * about_texture, * exit_texture;

	public:

        SDL_Rect r1{ 720+offsetX, 200 + offsetY, BUT_WIDTH, BUT_HEIGHT }, r2{ 720 + offsetX, 325 + offsetY, BUT_WIDTH, BUT_HEIGHT };
        SDL_Rect r3{ 770 + offsetX, 450 + offsetY, 200, BUT_HEIGHT }, r4{ 770 + offsetX, 575 + offsetY, 200, BUT_HEIGHT };

        void render_developer_window();

        void render_game_logo_window();

        void carrom_menu_background();

        void render_new_game_button();

        void render_leaderboard_button();

        void render_about_button();

        void render_exit_button();

        void main_menu_window();

        void reset_button_states();

        void handleMainMenuEvents(SDL_Event e);

};

