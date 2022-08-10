#include "../include/pch.h"
#include "../include/game.h"

int main()
{
	srand(time(NULL));
	GameState state = Menu;
	GameMode mode = None;

	int bulls = 0, cows = 0, lives = 1;
	char answer[10], guess[10];

	puts("Welcome to the Bulls and Cows");

	while (true)
	{
		if (state == Menu)
		{
			showMenu(state, mode);
			processChoice(&state, &mode);

			// FIXME This code is only executed when player starts the game from the main menu
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
			processChoice(&state, &mode);
		}

		if (state == Lose)
		{
			puts("Unfortunately, the game is over");
			printf("The answer is: %s", answer);

			showMenu(state, mode);
			processChoice(&state, &mode);
		}

		if (state == Play)
		{
			if (lives == 1) { puts("Last attempt"); }
			else { printf("You have %d lives left\n", lives); }

			fputs("Your guess: ", stdout);
			fgets(guess, strlen(answer) + 1, stdin); /* Reading no more than length of answer */
			fseek(stdin, 0, SEEK_END); /* Discarding unread characters from input stream */

			findTheBeasts(answer, guess, &bulls, &cows);

			printf("Bulls: %d\nCows: %d\n\n", bulls, cows);

			if (bulls == strlen(answer)) { state = Win; }
			else
			{
				lives--;
				if (lives <= 0) { mode = Lose; }
			}
		}
	}

	return 0;
}
