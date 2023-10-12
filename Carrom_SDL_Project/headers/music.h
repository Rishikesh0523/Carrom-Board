#pragma once
#include <SDL.h>
#include<SDL_mixer.h>
#include <iostream>

class Music {
	private:
		Mix_Music* backgroundmusic;
		Mix_Chunk* selectionmusic;
		const char* musicfilepath;

	public:
		Music(const char* musicpath) { musicfilepath = musicpath; }

		~Music() {
			Mix_FreeMusic(backgroundmusic);
			Mix_FreeChunk(selectionmusic);
		}

		void PlayBackgroundMusic(int num);

		void PauseBackgroundMusic();

		void SetBackgroundVolume(int volume);

		void PlayClickMusic();

};
