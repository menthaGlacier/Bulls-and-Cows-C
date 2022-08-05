#ifndef GAME_H
#define GAME_H

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

#endif /* GAME_H */
