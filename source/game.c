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
		puts("1 - Yes, continue\n" "2 - Yes, switch Game Mode\n" "3 - No, Exit the Game");
	}
}

void generateSequence(GameMode mode, char* sequence)
{
	// Words Game Mode Algorithm:
	// The algorithm opens "words.txt" file and reads from it a number that specifies
	// the size of the words array. It then reads words from file until the size limit
	// is reached, or until the words run out earlier.

	if (mode == Words)
	{
		FILE* file = NULL;
		int wordsAmount = 0;

		file = fopen("words.txt", "r");

		if (!file)
		{
			// TODO Error message here
		}

		fscanf(file, "%d", &wordsAmount);

		if (wordsAmount < MINWORDSAMOUNT || wordsAmount > MAXWORDSAMOUNT) /* TODO Add constants */
		{
			// TODO Error message here
		}

		// TODO Finish words reading, filtering and writing in array
		// TODO Finish random taking word from array

		fclose(file);
	}

	// Numbers Game Mode Algorithm:
	// The algorithm takes a random digit (in range of 0 to 9) from array of digits
	// and replaces it with 99, it then sorts array and decrease N, repeating the
	// process until the number of length of difficulty is created 

	if (mode == Numbers)
	{
		int N = 10;
		char* number = "";
		int buffer[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int difficulty = randomGenerator(MINNUMSIZE, MAXNUMSIZE); /* TODO Add constants */

		for (int i = 0; i < difficulty; i++)
		{
			int tryNumber = randomGenerator(0, N - 1);
			number += (buffer[tryNumber] + '0'); /* Converting int to char */

			buffer[tryNumber] = 99;
			sortNumbers(buffer, N); N -= 1;
		}

		strcpy(sequence, number);
	}
}

void findTheBeasts(char* answer, char* guess, int* bulls, int* cows)
{
	*bulls = 0, *cows = 0;

	for (int i = 0; i < strlen(guess); i++)
	{
		for (int j = 0; j < strlen(answer); j++)
		{
			if (guess[i] == answer[j])
			{
				if (i == j) { (*bulls) += 1; break; }

				else { (*cows) += 1; break; }
			}
		}
	}
}
