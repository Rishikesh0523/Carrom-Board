#include "headers/TextureManager.h"

void TextureManager::LTexture(SDL_Renderer* ren, SDL_Surface* surface, SDL_Texture* texture, SDL_Rect *r1, SDL_Rect *r2) {
    
    texture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(ren, texture, r1, r2);
    SDL_RenderPresent(ren);

}