
#include <stdio.h>
#include <stdlib.h>

#include "Main/Main.h"
#include "Application/FileReader.h"


int main(int argc, char ** argv)
{
	PrintArguments(argc, argv);

	if (!ArgumentsValid(argc, argv)) { return EXIT_FAILURE; }

	const char *const path = "D:/Programming/Projects/Visual Studio/SFR";
	ReadDirectory(path);

	DisplayStatistics();

	return EXIT_SUCCESS;
}

bool ArgumentsValid(int argc, char ** argv)
{
	return true;
}

void PrintArguments(int argc, char ** argv)
{
	printf("\n");
	printf("ARGUMENTS:\n");
	printf("----------------------------------------\n");
	printf("\n");

	printf("argc:\n");
	printf("\t%i\n", argc);

	printf("\n");

	printf("argv:\n");
	for (int i = 0; i < argc; i++)
	{
		printf("\t%s\n", *(argv + i));
	}

	printf("\n");
	printf("----------------------------------------\n");
	printf("\n");
}
