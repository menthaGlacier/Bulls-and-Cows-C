#include <stdio.h>
#include <stdbool.h>

#include "../include/game.h"


int main()
{
	GameState state = Menu;
	GameMode mode = None;

	puts("Welcome to the Bulls and Cows");
	showMenu(state, mode);

	while (true)
	{
		// ...
	}


	return 0;
}
