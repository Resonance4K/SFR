
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

#include "Application/FileReader.h"
#include "Utility/String.h"


// --- Function Prototypes --- //

void ReadDirectory(const char *const path, const unsigned int depth);
DIR * GetDirectory(const char *const path);
bool IsValidDirectory(DIR * dir);
bool IsRootDirectory(const unsigned int depth);
char * GetFullPath(const char *const path, const char *const entry_name);

void ReadFile(const char *const path);
FILE * GetFile(const char *const path, const char *const mode);
bool IsValidFile(FILE * file);
char * GetFileExtension(const char *const path);


// --- Constant Definitions --- //

#define ROOT_DEPTH    0


// Flag that keeps track of whether the root directory that was provided by the user is valid.
bool IsValidRootDirectory = true;

// Defined in "FileReader.h".
void ReadRootDirectory(const char *const path)
{
	ReadDirectory(path, ROOT_DEPTH);
}

// Reads a directory specified by the path and processes its contents.
void ReadDirectory(const char *const path, const unsigned int depth)
{
	DIR * dir = GetDirectory(path);

	if (!IsValidDirectory(dir))
	{
		if (IsRootDirectory(depth))
		{
			IsValidRootDirectory = false;
			printf("[ERROR] Not a valid directory: %s\n", path);
		}

		return;
	}
	
	struct dirent * ent;

	while ((ent = readdir(dir)) != NULL)
	{
		const char *const entry_name = ent->d_name;
		const unsigned int entry_type = ent->d_type;

		if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0) { continue; }
		if (*entry_name == '.') { continue; }

		const char *const fullpath = GetFullPath(path, entry_name);
		
		printf("[PATH] %s\n", fullpath);

		if (entry_type == DT_DIR)
		{
			ReadDirectory(fullpath, depth + 1);
		}
		else if (entry_type == DT_REG)
		{
			ReadFile(fullpath);
		}

		free(fullpath);
	}

	closedir(dir);
}

// Returns the directory handle of the directory specified by the path or NULL if the directory cannot be opened.
DIR * GetDirectory(const char *const path)
{
	return opendir(path);
}

// Returns true if the directory being read is valid (not NULL) and false otherwise.
bool IsValidDirectory(DIR * dir)
{
	return dir != NULL;
}

// Returns true if the directory being read is the root directory and false otherwise.
bool IsRootDirectory(const unsigned int depth)
{
	return depth == ROOT_DEPTH;
}

// Returns the full path resulting from a concatenation of the path and entry name variables.
// NOTE: This allocates memory on the heap which must be freed after use.
char * GetFullPath(const char *const path, const char *const entry_name)
{
	const unsigned int path_length = strlen(path);
	const unsigned int entry_name_length = strlen(entry_name);

	const unsigned int length = path_length + entry_name_length + 1;

	char *const fullpath = malloc( length * sizeof( *fullpath ) + 1 );

	strcpy(fullpath, path);
	strcat(fullpath, "/");
	strcat(fullpath, entry_name);
	*(fullpath + length) = '\0';

	return fullpath;
}

// Reads a file specified by the path and processes it if it is a supported source file.
void ReadFile(const char *const path)
{
	FILE * file = GetFile(path, "r");

	if (!IsValidFile(file)) { return; }

	const char *const file_extension = GetFileExtension(path);
	printf("File Extension = %s\n", file_extension);

	free(file_extension);
}

// Returns the file handle of the file specified by the path in the specified mode or NULL if the file cannot be opened.
FILE * GetFile(const char *const path, const char *const mode)
{
	return fopen(path, mode);
}

// Returns true if the file being read is valid (not NULL) and false otherwise.
bool IsValidFile(FILE * file)
{
	return file != NULL;
}

// Returns the extension of a file or NULL if no extension exists.
// NOTE: This returns a string whose memory has been allocated on the heap and must be freed after use.
char * GetFileExtension(const char *const path)
{
	const int extension_index = StrFindBack(path, '.');

	if (extension_index == -1) { return NULL; }

	return StrSubstr(path, extension_index + 1, strlen(path));
}

// Defined in "FileReader.h".
void DisplayStatistics(void)
{

}
