#pragma once

#include<SDL.h>
#include<SDL_ttf.h>
#include<iostream>

class FontManager {
	
	public:

		static void LFont(SDL_Renderer* ren, SDL_Surface* surface, SDL_Texture* texture, TTF_Font* font, std::string text, SDL_Color color, SDL_Rect* r1);

};
