
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Application/FileReader.h"
#include "Utility/String.h"


// --- Function Prototypes --- //

bool IsValidArgumentCount(int argc);
void PrintArguments(int argc, char ** argv);


// --- Constant Definitions --- //

#define TOTAL_DIRECTORY_COUNT    1


// The entry point of the program.
int main(int argc, char ** argv)
{
	PrintArguments(argc, argv);

	if (!IsValidArgumentCount(argc))
	{
		printf("[ERROR] Expected %i argument but instead received %i arguments!\n", TOTAL_DIRECTORY_COUNT, (argc - 1));
		return EXIT_FAILURE;
	}

	StrReplaceAll(*(argv + 1), '\\', '/');

	const char *const path = *(argv + 1);
	ReadRootDirectory(path);

	DisplayStatistics();
	
	return EXIT_SUCCESS;
}

// Checks the number of arguments provided to the program by the user.
// Returns true if it equals the expected number of arguments and false otherwise.
bool IsValidArgumentCount(int argc)
{
	return (argc - 1) == TOTAL_DIRECTORY_COUNT;
}

// Prints the argument count and argument vector.
void PrintArguments(int argc, char ** argv)
{
	printf("\n");
	printf("ARGUMENTS:\n");
	printf("----------------------------------------\n");
	printf("\n");

	printf("argc:\n");
	printf("\t%i\n", (argc - 1));

	printf("\n");

	printf("argv:\n");
	for (int i = 1; i < argc; i++)
	{
		printf("\t%s\n", *(argv + i));
	}

	printf("\n");
	printf("----------------------------------------\n");
	printf("\n");
}
