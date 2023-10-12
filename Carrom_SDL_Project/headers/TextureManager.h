#pragma once

#include<SDL.h>

class TextureManager {

	public:

		static void LTexture(SDL_Renderer* ren, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect *r1, SDL_Rect *r2);
		
};
