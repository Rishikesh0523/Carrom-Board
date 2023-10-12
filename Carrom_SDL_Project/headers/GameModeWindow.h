#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "MainMenu.h"

class NewGameModes {

	private:

        bool single_player_button_state = true;
        bool multiplayer_button_state = true;
        bool over_LAN_button_state = true;
        bool back_button_state = true;
        int offsetX = 100;
        int offsetY = 100;

        SDL_Texture* single_player_texture, * multiplayer_texture, * over_LAN_texture, * back_texture;
        SDL_Surface* single_player_surface, * multiplayer_surface, * over_LAN_surface, * back_surface;

    public:

        SDL_Rect r1{ 720 + offsetX, 200 + offsetY, BUT_WIDTH, BUT_HEIGHT }, r2{ 720 + offsetX, 325 + offsetY, BUT_WIDTH, BUT_HEIGHT };
        SDL_Rect r4{ 770 + offsetX, 575 + offsetY, 200, BUT_HEIGHT }, r7{ 745 + offsetX, 450 + offsetY, 250, BUT_HEIGHT };

        void render_singleplayer_button();
        
        void render_multiplayer_button();

        void render_overlan_button();

        void render_back_button();

        void render_mode_buttons();

        void reset_mode_buttons_states();
        
        void handleNewGameModeEvents(SDL_Event e);

};