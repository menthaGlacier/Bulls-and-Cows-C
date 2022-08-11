#include "../include/pch.h"
#include "../include/game.h"

int main()
{
	srand(time(NULL));
	Game game;

	game.state = Menu;
	game.mode = None;

	puts("Welcome to the Bulls and Cows");

	while (true)
	{
		if (game.state == Menu)
		{
			showMenu(game.state, game.mode);
			processChoice(&game);
		}

		if (game.state == Win)
		{
			puts("Congratulations, you've won! Thanks for playing!");

			showMenu(game.state, game.mode);
			processChoice(&game);
		}

		if (game.state == Lose)
		{
			puts("Unfortunately, the game is over");
			printf("The answer was: %s\n", game.answer);

			showMenu(game.state, game.mode);
			processChoice(&game);
		}

		if (game.state == Play)
		{
			if (game.lives == 1) { puts("Last attempt"); }
			else { printf("You have %d lives left\n", game.lives); }

			fputs("Your guess: ", stdout);
			fgets(game.guess, strlen(game.answer) + 1, stdin); /* Reading no more than length of answer */
			fseek(stdin, 0, SEEK_END); /* Discarding unread characters from input stream */

			findTheBeasts(game.answer, game.guess, &game.bulls, &game.cows);

			printf("Bulls: %d\nCows: %d\n\n", game.bulls, game.cows);

			if (game.bulls == strlen(game.answer)) { game.state = Win; }
			else
			{
				game.lives--;
				if (game.lives <= 0) { game.state = Lose; }
			}
		}
	}

	return 0;
}
