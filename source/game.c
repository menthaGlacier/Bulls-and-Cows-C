#include "../include/game.h"

void showMenu(GameState state, GameMode mode)
{
	if (state == Menu || mode == None)
	{
		puts("Main Menu");
		puts("1 - Game Mode - Words\n" "2 - Game Mode - Numbers\n" "3 - Exit");
	}
}
