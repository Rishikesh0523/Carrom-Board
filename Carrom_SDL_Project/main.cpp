#include<SDL.h>
#include<SDL_image.h>
#include "headers/MainFrame.h"
#include "headers/MainMenu.h"
#include "headers/GameModeWindow.h"
#include "headers/AboutWindow.h"
#include "headers/music.h"
#include "headers/OverLANModes.h"
#include "headers/PlayerIntro.h"
#include "headers/SinglePlayerGame.h"
#include "headers/MultiplayerModes.h"
#include "headers/TwoPlayerGame.h"
#include "headers/TwoPlayerIntro.h"
#include "headers/Leaderboard.h"

Initialization* MainWindow = nullptr;
MainMenu MenuWindow;
NewGameModes ModeWindow;
AboutSection AboutWindow;
Music* BackMusic;
Music* ClickSound;
OverLANModes LANModeWindow;
PlayerIntro IntroWindow;
SinglePlayerGame SinglePlayerGameWindow;
PlayerInfo Info;
MultiPlayerModes MultiPlayerModeWindow;
TwoPlayerGame TwoPlayerGameWindow;
TwoPlayerIntro TwoPlayerIntroWindow;
TwoPlayerInfo TwoInfo;
Leaderboard LeaderboardWindow;



windowStates currState;

int main(int argc, char* argv[]) {

	currState = MAINMENU;

	MainWindow = new Initialization();
	BackMusic = new Music("music/background_one.mp3");
	ClickSound = new Music("music/selection_music.wav");

	MainWindow->windowInit("CarromKing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, false);
	MenuWindow.render_developer_window();
	MenuWindow.render_game_logo_window();
	BackMusic->PlayBackgroundMusic(-1);
	MenuWindow.main_menu_window();

	SDL_Event event;

	while (MainWindow->runningState()) {

		if (SDL_PollEvent(&event)) {
			MainWindow->handleMainEvent(event);

			switch (currState) {
				case MAINMENU:
					MenuWindow.handleMainMenuEvents(event);
					break;

				case NEWGAMEMODES:
					ModeWindow.handleNewGameModeEvents(event);
					break;

				case ABOUT:
					AboutWindow.handleAboutWindowEvents(event);
					break;

				case SINGLEPLAYERINTRO:
					IntroWindow.handlePlayerIntroEvents(event);
					break;

				case SINGLEPLAYERGAME:
					SinglePlayerGameWindow.handleSinglePlayerGameEvents(event);
					break;

				case TWOPLAYERINTRO:
					TwoPlayerIntroWindow.handleTwoPlayerIntroEvents(event);
					break;

				case TWOPLAYERGAME:
					TwoPlayerGameWindow.handleTwoPlayerGameEvents(event);
					break;

				case MULTIPLAYERGAMEMODES:
					MultiPlayerModeWindow.handleMultiPlayerModesEvents(event);
					break;

				case OVERLANMODES:
					LANModeWindow.handleOverLANModesEvents(event);
					break;

				default:
					break;

			}
		}


	}

	MainWindow->clean();

	return 0;
}