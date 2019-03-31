
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

#include "Application/FileReader.h"


// --- Function Prototypes --- //

void ReadDirectory(const char *const path, const unsigned int depth);
DIR * GetDirectory(const char *const path);
void ReadFile(const char *const path);
FILE * GetFile(const char *const path, const char *const mode);


// --- Constant Definitions --- //

#define ROOT_DEPTH    0


// Flag that keeps track of whether the root directory that was provided by the user is valid.
bool ValidRootDirectory = false;

// Defined in "FileReader.h".
void ReadRootDirectory(const char *const path)
{
	ReadDirectory(path, ROOT_DEPTH);
}

// Reads a directory specified by the path and processes its contents.
void ReadDirectory(const char *const path, const unsigned int depth)
{
	DIR * dir = GetDirectory(path);

	if (dir == NULL && depth == ROOT_DEPTH)
	{
		printf("[ERROR] Not a valid directory: %s\n", path);
		return;
	}
	
	struct dirent * ent;
	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) { continue; }

		char fullpath[1024];
		strcpy(fullpath, path);
		strcat(fullpath, "/");
		strcat(fullpath, ent->d_name);
		
		printf("%s\n", fullpath);
		printf("[DEPTH=%i]\n", depth);

		if (ent->d_type == DT_DIR)
		{
			printf("[DIR]\n");
			ReadDirectory(fullpath, depth + 1);
		}
		else if (ent->d_type == DT_REG)
		{
			printf("[REG]\n");
		}
	}

	closedir(dir);
}

// Returns the directory handle of the directory specified by the path or NULL if the directory cannot be opened.
DIR * GetDirectory(const char *const path)
{
	return opendir(path);
}

// Reads a file specified by the path and processes it if it is a supported source file.
void ReadFile(const char *const path)
{
	FILE * file = GetFile(path, "r");
}

// Returns the file handle of the file specified by the path in the specified mode or NULL if the file cannot be opened.
FILE * GetFile(const char *const path, const char *const mode)
{
	return fopen(path, mode);
}

// Defined in "FileReader.h".
void DisplayStatistics(void)
{

}
