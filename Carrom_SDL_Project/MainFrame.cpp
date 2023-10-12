#include "headers/MainFrame.h"
#include <iostream>



void Initialization::windowInit(const char* title, int x_pos, int y_pos, int p_w, int p_h, bool fullscreen) {

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL is initialized successfully!! " << std::endl;

		window = SDL_CreateWindow(title, x_pos, y_pos, p_w, p_h, flags);

		if (window) {
			std::cout << "Window created!!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer) {
			std::cout << "Renderer created!!" << std::endl;
		}

		if (TTF_Init() == -1) {
			std::cout << "Could not initialize the TTF!! Error: " << TTF_GetError() << std::endl;
		}

		fontType = TTF_OpenFont("fonts/Roboto-Black.ttf", 300);

		if (fontType != nullptr) {
			std::cout << "Font is initialized!!" << std::endl;
		}

		is_running = true;

	}
	else {
		is_running = false;
	}

}

void Initialization::handleMainEvent(SDL_Event e) {
	switch (e.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		default:
			break;
	}
}

void Initialization::clean() {

	std::cout << "Game is cleaned" << std::endl;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(fontType);
	SDL_Quit();

}