#ifndef GAME_H
#define GAME_H

#define MINWORDSAMOUNT 10
#define MAXWORDSAMOUNT 255

#define MINWORDSIZE 4
#define MAXWORDSIZE 9

#define MINNUMSIZE 4
#define MAXNUMSIZE 8 /* Cannot exceed size of 10 */

#include "pch.h"
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

void showMenu(GameState state, GameMode mode);

void generateSequence(GameMode mode, char* sequence);

void findTheBeasts(char* answer, char* guess, int* bulls, int* cows);

#endif /* GAME_H */
