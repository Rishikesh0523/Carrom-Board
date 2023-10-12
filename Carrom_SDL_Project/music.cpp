#include "headers/music.h"


void Music::PlayBackgroundMusic(int num) {

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		std::cout << "Audio Library not working!!" << Mix_GetError() << std::endl;
	}
	backgroundmusic = Mix_LoadMUS(musicfilepath);

	if (backgroundmusic != nullptr) {
		Mix_PlayMusic(backgroundmusic, num);
	}

}

void Music::PauseBackgroundMusic() {

	Mix_PauseMusic();

}

void Music::SetBackgroundVolume(int volume) {

	Mix_VolumeMusic(volume);

}

void Music::PlayClickMusic() {

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		std::cout << "Audio Library not working!!" << Mix_GetError() << std::endl;
	}

	selectionmusic = Mix_LoadWAV(musicfilepath);

	if (selectionmusic != nullptr) {
		Mix_PlayChannel(-1, selectionmusic, 0);
	}

}