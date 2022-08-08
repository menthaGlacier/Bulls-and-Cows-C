#include "../include/functions.h"

int randomNumberGenerator(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

void toLowercase(char* word)
{
	for (int i = 0; i < strlen(word); i++)
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
	for (int i = 0; i < strlen(str); i++)
	{
		for (int j = 0; j < strlen(str) - 1; j++)
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
	if (!word)
	{
		puts("A word passed to the filter was an empty pointer");
		exit(-5);
	}

	int wordLen = strlen(word);

	// Length check
	if (wordLen < MINWORDSIZE || wordLen > MAXWORDSIZE)
	{
		return false;
	}

	// Letter and isogram check
	for (int i = 0; i < wordLen; i++)
	{
		sortString(word);

		if (!((word[i] >= 'a' && word[i] <= 'z') ||
			(word[i] >= 'A' && word[i] <= 'Z'))) { return false; }

		if (word[i + 1] == word[i]) { return false; }
	}

	toLowercase(word);
	return true;
}