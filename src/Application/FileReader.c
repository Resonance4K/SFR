
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

#include "Application/FileReader.h"


// --- Function Prototypes --- //

void ReadSubDirectory(const char *const path);
DIR * GetDirectory(const char *const path);
void ReadFile(const char *const path);
FILE * GetFile(const char *const path, const char *const mode);


// Reads the root directory specified by the path that is provided by the user from the argument vector.
void ReadRootDirectory(const char *const path)
{
	DIR * dir = GetDirectory(path);

	if (dir == NULL) { return; }
	
	struct dirent * ent;
	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) { continue; }

		printf("%s\n", ent->d_name);
	}

	closedir(dir);
}

// Reads the sub directories that reside within the directory specified by the path.
void ReadSubDirectory(const char *const path)
{

}

// Returns the directory handle of the directory specified by the path or NULL if the directory does not exist.
DIR * GetDirectory(const char *const path)
{
	return opendir(path);
}

// Reads a file specified by the path and processes it if it is a supported source file.
void ReadFile(const char *const path)
{
	FILE * file = GetFile(path, "r");
}

// Returns the file handle of the file specified by the path in the specified mode or NULL if the file does not exist.
FILE * GetFile(const char *const path, const char *const mode)
{
	return fopen(path, mode);
}

// Displays the statistics of all supported source files that were read from the provided root directory.
void DisplayStatistics(void)
{

}
