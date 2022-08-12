#include "../include/functions.h"

int randomNumberGenerator(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

void toLowercase(char* word)
{
	for (size_t i = 0; i < strlen(word); i++)
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
		{
			// In ASCII uppercase letter 'A' has a decimal value of 65,
			// a lowercase letter 'a' has value of 97 thus, by adding 32
			// to any uppercase letter we get a lowercase letter
			word[i] += 32;
		}
	}
}

void sortNumbers(int arr[], int numOfElementsToSort)
{
	for (int i = 0; i < numOfElementsToSort; i++)
	{
		for (int j = 0; j < numOfElementsToSort - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void sortString(char* str)
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		for (size_t j = 0; j < strlen(str) - 1; j++)
		{
			if (str[j] > str[j + 1])
			{
				char temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
			}
		}
	}
}

bool filter(char* word)
{
	// Creating a copy of the string so as not to change the original
	// one when sorting for a letter and isogram check
	char wordBuffer[255] = "";
	strcpy(wordBuffer, word);

	if (!wordBuffer)
	{
		errorHandler(ERR_ALLOC);
	}

	int wordLen = strlen(wordBuffer);

	// Length check
	if (wordLen < MINWORDSIZE || wordLen > MAXWORDSIZE)
	{
		return false;
	}

	// Sorting for an isogram check
	sortString(wordBuffer);

	// Letters and isogram check
	for (int i = 0; i < wordLen; i++)
	{

		if (!((wordBuffer[i] >= 'a' && wordBuffer[i] <= 'z') ||
			(wordBuffer[i] >= 'A' && wordBuffer[i] <= 'Z'))) { return false; }

		if (wordBuffer[i + 1] == wordBuffer[i]) { return false; }
	}

	// After successfully passing the checks, we translate the
	// original string into lowercase
	toLowercase(word);
	return true;
}