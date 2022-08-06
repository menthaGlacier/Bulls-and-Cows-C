#include "../include/pch.h"
#include "../include/game.h"

int main()
{
	GameState state = Menu;
	GameMode mode = None;

	int bulls = 0, cows = 0, lives = 1;
	char answer[10], guess[10];

	puts("Welcome to the Bulls and Cows");
	showMenu(state, mode);
	// TODO game start and processing input

	while (true)
	{
		if (state == Menu)
		{
			generateSequence(mode, answer);
			printf("Try to guess the %d ", strlen(answer));

			if (mode == Words) { puts("letter word"); }
			else if (mode == Numbers) { puts("digit number"); }

			lives = strlen(answer) * 2;
		}

		if (state == Win)
		{
			puts("Congratulations, you've won! Thanks for playing!");

			showMenu(state, mode);
			// TODO processing input
		}

		if (lives == 0)
		{
			puts("Unfortunately, the game is over");
			puts("The answer is: ", answer);

			showMenu(state, mode);
			// TODO processing input
		}
	}

	return 0;
}
