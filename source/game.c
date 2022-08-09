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
			puts("An error occured while trying to open file");
			exit(-1);
		}

		fscanf(file, "%d", &maxWordsAmount);

		if (maxWordsAmount < MINWORDSAMOUNT || maxWordsAmount > MAXWORDSAMOUNT)
		{
			printf("Amount of words should be in [%d; %d] range\n",
				MINWORDSAMOUNT, MAXWORDSAMOUNT);
			exit(-2);
		}

		words = (char**)(malloc(maxWordsAmount * sizeof(char*)));
		if (!words)
		{
			puts("An error occurred while trying to allocate memory for a words array");
			exit(-3);
		}

		int readWordsAmount = 0;
		for (int i = 0; i < maxWordsAmount; i++)
		{
			char buffer[255] = "";

			words[i] = (char*)(malloc((MAXWORDSIZE + 1) * sizeof(char)));
			if (!words[i])
			{
				puts("An error occurred while trying to allocate memory for a word");
				exit(-4);
			}

			if (fscanf(file, " %s", buffer) == EOF) { readWordsAmount = i; break; }
			if (!filter(buffer)) { --i; continue; }
			strcpy(words[i], buffer);
		}

		if (readWordsAmount < MINWORDSAMOUNT)
		{
			printf("The number of words read is less than the required minimum of %d words",
				MINWORDSAMOUNT);
			exit(-6);
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
	// The algorithm takes a random digit (in range of 0 to 9) from an array of digits
	// and replaces it with 99, it then sorts array and decrease N, repeating the
	// process until the number of length of difficulty is created 

	if (mode == Numbers)
	{
		int N = 10;
		char* number = NULL;
		int buffer[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int difficulty = randomNumberGenerator(MINNUMSIZE, MAXNUMSIZE);

		number = (char*)(malloc((difficulty + 1) * sizeof(char)));
		if (!number)
		{
			puts("An error occured while trying to allocate memory for a number");
			exit(-7);
		}

		for (int i = 0; i < difficulty; i++)
		{
			int tryNumber = randomNumberGenerator(0, N - 1);
			number[i] = (buffer[tryNumber] + '0'); /* Converting int to char */

			buffer[tryNumber] = 99;
			sortNumbers(buffer, N); N -= 1;
		}

		number[difficulty] = '\0';
		strcpy(sequence, number);
		free(number);
	}
}

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
