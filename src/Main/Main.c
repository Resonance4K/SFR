
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Application/FileReader.h"
#include "Utility/String.h"



bool SourceFileReader(int argc, char ** argv);
bool IsValidArgumentCount(int argc);

void DisplayDirectory(const char *const path);



#define TOTAL_ARGUMENT_COUNT    1



// The entry point of the program executed by the Operating System (OS).
int main(int argc, char ** argv)
{
	const int program_status = SourceFileReader(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;

	printf("Program terminated with status: %s\n", program_status == EXIT_SUCCESS ? "SUCCESS" : "FAILURE");
	printf("\n");

	return program_status;
}

// The entry point of the program executed by the user.
// Returns true if the program executed successfully and false otherwise.
bool SourceFileReader(int argc, char ** argv)
{
	StrReplaceAll(*(argv + 1), '\\', '/');

	if (!IsValidArgumentCount(argc))
	{
		printf("[ERROR] Expected %i argument but instead received %i arguments!\n", TOTAL_ARGUMENT_COUNT, (argc - 1));
		return false;
	}

	const char *const path = *(argv + 1);

	if (!IsValidDirectoryPath(path))
	{
		printf("[ERROR] The path specified is not a valid directory: %s\n", path);
		return false;
	}

	DisplayDirectory(path);

	InitFileReader();

	ReadDirectory(path);

	DisplayStatistics();

	return true;
}

// Returns true if the number of arguments provided equals the expected argument count and false otherwise.
bool IsValidArgumentCount(int argc)
{
	return (argc - 1) == TOTAL_ARGUMENT_COUNT;
}

// Displays the directory path that the program will read from.
void DisplayDirectory(const char *const path)
{
	printf("\n");
	printf("Reading directory:\n");
	printf("%s\n", path);
	printf("\n");
}
