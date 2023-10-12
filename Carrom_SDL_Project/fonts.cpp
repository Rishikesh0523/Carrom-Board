#include "headers/MainFrame.h"
#include "headers/fonts.h"

void FontManager::LFont(SDL_Renderer* ren, SDL_Surface* surface, SDL_Texture* texture, TTF_Font* font, std::string text, SDL_Color color, SDL_Rect* r1) {

	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderCopy(ren, texture, NULL, r1);
	SDL_RenderPresent(ren);

}