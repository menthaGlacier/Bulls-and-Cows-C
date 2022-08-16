#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include "constants.h"
#include "errorHandler.h"
#include "functions.h"

typedef enum GameState
{
	Menu = 0,
	Play = 1,
	Win = 2,
	Lose = 3
} GameState;

typedef enum GameMode
{
	None = 0,
	Words = 1,
	Numbers = 2
} GameMode;

typedef struct Game
{
	GameState state;
	GameMode mode;

	int bulls, cows, lives;
	char answer[10], guess[10];
} Game;

void showMenu(GameState state, GameMode mode);

void initGameSession(Game* game);

void processChoice(Game* game);

void generateSequence(GameMode mode, char* sequence);

void findTheBeasts(char* answer, char* guess, int* bulls, int* cows);

#endif /* GAME_H */
