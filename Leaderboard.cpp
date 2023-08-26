#include "headers/MainFrame.h"
#include "headers/TextureManager.h"
#include "headers/fonts.h"
#include "headers/Leaderboard.h"
#include "headers/SinglePlayerGame.h"
#include "headers/TwoPlayerGame.h"

extern Initialization* MainWindow;

void Leaderboard::display_score_window() {
	surface = IMG_Load("assets/score.png");
	TextureManager::LTexture(MainWindow->renderer, surface, texture, NULL, NULL);
}