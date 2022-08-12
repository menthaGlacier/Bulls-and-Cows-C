#include "../include/game.h"

void showMenu(GameState state, GameMode mode)
{
	if (state == Menu || mode == None)
	{
		puts("Main Menu");
		puts("1 - Game Mode - Words\n" "2 - Game Mode - Numbers\n" "3 - Exit");
	}

	else if (state == Win || state == Lose)
	{
		puts("Do you want to play again?");
		puts("1 - Continue\n" "2 - Switch Game Mode\n" "3 - Exit to the Main Menu");
	}
}

void initGameSession(Game* game)
{
	generateSequence(game->mode, game->answer);
	printf("Try to guess the %d ", strlen(game->answer));

	if (game->mode == Words) { puts("letter word"); }
	else if (game->mode == Numbers) { puts("digit number"); }

	game->bulls = 0, game->cows = 0;
	game->lives = strlen(game->answer) * 2;
}

void processChoice(Game* game)
{
	char choice = '0';

	while (true)
	{
		fputs("Your choice: ", stdout);
		choice = getchar();
		fseek(stdin, 0, SEEK_END); /* Discarding unread characters from input stream */

		// From the main menu, the player can start a session with two game modes or exit
		if (game->state == Menu)
		{
			if (choice == '1')
			{
				game->mode = Words;
				game->state = Play;
				initGameSession(game);
				break;
			}

			else if (choice == '2')
			{
				game->mode = Numbers;
				game->state = Play;
				initGameSession(game);
				break;
			}

			else if (choice == '3')
			{
				exit(0);
			}
		}

		// When the game is over, regardless of winning or losing, the player can start
		// a new session, change the game mode or return to the main menu
		else if (game->state == Win || game->state == Lose)
		{
			if (choice == '1')
			{
				game->state = Play;
				initGameSession(game);
				break;
			}

			else if (choice == '2')
			{
				game->state = Play;
				if (game->mode == Words) { game->mode = Numbers; }
				else if (game->mode == Numbers) { game->mode = Words; }
				initGameSession(game);
				break;
			}

			else if (choice == '3')
			{
				game->state = Menu;
				game->mode = None;
				break;
			}

		}
	}
}

void generateSequence(GameMode mode, char* sequence)
{
	// Words Game Mode Algorithm:
	// The algorithm opens "words.txt" file and reads from it a number that specifies
	// the size of the words array. It then allocates memory to an array of strings and
	// reads words from file until the size limit is reached, or until the words run out earlier. 
	// Each word passes through a filter and after passing successfully is converted to lowercase
	// and written in the array. The sequence is then randomly selected from the array and array gets deleted

	if (mode == Words)
	{
		FILE* file = NULL;
		char** words = NULL;
		int maxWordsAmount = 0;

		file = fopen("words.txt", "r");

		if (!file)
		{
			errorHandler(1, "words.txt");
		}

		fscanf(file, "%d", &maxWordsAmount);

		if (maxWordsAmount < MINWORDSAMOUNT || maxWordsAmount > MAXWORDSAMOUNT)
		{
			errorHandler(3, MINWORDSAMOUNT, MAXWORDSAMOUNT);
		}

		words = (char**)(malloc(maxWordsAmount * sizeof(char*)));
		if (!words)
		{
			errorHandler(2);
		}

		int readWordsAmount = 0;
		for (int i = 0; i < maxWordsAmount; i++)
		{
			char buffer[255] = "";

			words[i] = (char*)(malloc((MAXWORDSIZE + 1) * sizeof(char)));
			if (!words[i])
			{
				errorHandler(2);
			}

			if (fscanf(file, " %s", buffer) == EOF) { readWordsAmount = i; break; }
			if (!filter(buffer)) { --i; continue; }
			strcpy(words[i], buffer);
		}

		if (readWordsAmount < MINWORDSAMOUNT || readWordsAmount > MAXWORDSAMOUNT)
		{
			errorHandler(3, MINWORDSAMOUNT, MAXWORDSAMOUNT);
		}

		strcpy(sequence, words[randomNumberGenerator(0, readWordsAmount)]);

		// Freeing up memory and closing the file
		// Freeing readWordsAmount-times, because memory allocation stops
		// after the last word is read 
		for (int i = 0; i < readWordsAmount; i++) { free(words[i]); }
		free(words);
		fclose(file);
	}

	// Numbers Game Mode Algorithm:
	// The algorithm gets a random difficulty and then allocates memory to an array the size of the difficulty.
	// It then takes a random number in the range of 0 to N from the pool of digits, writes it to the resulting array
	// and replaces that digit with 99. Sorting the array and decrementing N removes the digit from the pool.
	// This process is repeated difficulty-times until the final number sequence is created

	if (mode == Numbers)
	{
		int N = 10;
		char* number = NULL;
		int pool[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int difficulty = randomNumberGenerator(MINNUMSIZE, MAXNUMSIZE);

		number = (char*)(malloc((difficulty + 1) * sizeof(char)));
		if (!number)
		{
			errorHandler(2);
		}

		for (int i = 0; i < difficulty; i++)
		{
			int tryNumber = randomNumberGenerator(0, N - 1);
			number[i] = (pool[tryNumber] + '0'); /* Converting int to char */

			// 99 is a placeholder, any number greater than 9 will work,
			// to remove a digit from the pool
			pool[tryNumber] = 99;
			sortNumbers(pool, N); N -= 1;
		}

		number[difficulty] = '\0';
		strcpy(sequence, number);
		free(number);
	}
}

// This function finds bulls and cows by comparing the player's guess with an answer
void findTheBeasts(char* answer, char* guess, int* bulls, int* cows)
{
	*bulls = 0, *cows = 0;

	for (size_t i = 0; i < strlen(guess); i++)
	{
		for (size_t j = 0; j < strlen(answer); j++)
		{
			if (guess[i] == answer[j])
			{
				if (i == j) { (*bulls) += 1; break; }

				else { (*cows) += 1; break; }
			}
		}
	}
}
