
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Application/SFR.h"
#include "Application/FileReader.h"
#include "Utility/String.h"



bool IsValidArgumentCount(const int argc);

int GetDepthFromArgs(const char *const argument);

void DisplayDirectory(const char *const path);



#define MINIMUM_ARGUMENT_COUNT    1
#define MAXIMUM_ARGUMENT_COUNT    2



// Defined in "SFR.h".
bool SourceFileReader(int argc, char ** argv)
{
	if (!IsValidArgumentCount(argc))
	{
		printf("[ERROR] Expected a minimum of %i argument and a maximum of %i arguments but instead received %i arguments!\n", MINIMUM_ARGUMENT_COUNT, MAXIMUM_ARGUMENT_COUNT, (argc - 1));
		return false;
	}

	StrReplaceAll(*(argv + 1), '\\', '/');
	const char *const path = *(argv + 1);

	if (!IsValidDirectoryPath(path))
	{
		printf("[ERROR] The path specified is not a valid directory: %s\n", path);
		return false;
	}

	const int depth = GetDepthFromArgs(*(argv + 2));

	DisplayDirectory(path);

	InitFileReader();
	ReadDirectory(path, depth);

	DisplayStatistics();

	return true;
}

// Returns true if the number of arguments provided is in between the minimum (inclusive) and maximum (inclusive) argument counts and false otherwise.
bool IsValidArgumentCount(const int argc)
{
	return (argc - 1) >= MINIMUM_ARGUMENT_COUNT && (argc - 1) <= MAXIMUM_ARGUMENT_COUNT;
}

// Returns an integer representing the directory traversal depth extracted from the argument or a default depth if the argument does not exist or if the extraction has failed.
int GetDepthFromArgs(const char *const argument)
{
	int depth = DEFAULT_DEPTH;

	if (argument != NULL)
	{
		if (StrStartsWith(argument, 1, "d:"))
		{
			const int *const extracted_depth = StrToInt(argument + 2);

			if (extracted_depth != NULL)
			{
				depth = *extracted_depth;
			}

			free(extracted_depth);
		}
	}

	return depth;
}

// Displays the directory path that the program will read from.
void DisplayDirectory(const char *const path)
{
	printf("\n");
	printf("Reading directory:\n");
	printf("%s\n", path);
}
