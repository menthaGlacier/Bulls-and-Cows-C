#include "../include/functions.h"

int randomNumberGenerator(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

void errorHandler(int errCode, ...)
{
	puts("");

	va_list argptr;
	
	switch (errCode)
	{
	// Error code #1 indicates an error with opening a file
	// An additional argument specifies the file name
	case 1:
		fprintf(stderr, "An error occured while trying to open a %s file\n",
			va_arg(argptr, char*));
		break;

	// Error code #1 indicates an error with memory allocation
	case 2:
		fprintf(stderr, "An error occured while trying to allocate memory\n");
		break;

	// Error code #3 indicates an error with the amount of loaded valid words
	// Two additional arguments specify the minimum and maximum amount of words 
	case 3:
		fprintf(stderr, "An invalid amount of valid words were loaded. "
			"Their amount must be in [%d, %d] range\n",
			va_arg(argptr, int), va_arg(argptr, int));
		break;

	// Error code #4 indicates an error with the word passed to the filter
	case 4:
		fprintf(stderr, "A word passed to the filter was an empty pointer\n");
		break;

	// In the case of an unknown error code
	default:
		fprintf(stderr, "Unknown error code #%d\n", errCode);
		break;
	}

	va_end(argptr);
	exit(errCode);
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
		errorHandler(4);
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