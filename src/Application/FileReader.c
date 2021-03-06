
// Provides the definitions for the DT_DIR and DT_REG constants on Linux systems
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "Application/FileReader.h"
#include "Application/Extensions.h"
#include "Application/Readers.h"
#include "Utility/String.h"



bool IsValidDirectory(DIR * dir);
char * GetFullPath(const char *const path, const char *const entry_name);

void ReadFile(const char *const path);
bool IsValidFile(FILE * file);
char * GetFileExtension(const char *const path);



// Defined in "FileReader.h".
void InitFileReader(void)
{
	InitReaders();
}

// Defined in "FileReader.h".
void ReadDirectory(const char *const path, const int depth)
{
	// Stop traversing and processing directories when no further traversals are required due to the target depth being reached
	if (depth < 0) { return; }

	DIR * dir = opendir(path);

	if (!IsValidDirectory(dir))
	{
		closedir(dir);
		return;
	}
	
	struct dirent * ent;

	while ((ent = readdir(dir)) != NULL)
	{
		const char *const entry_name = ent->d_name;
		const unsigned int entry_type = ent->d_type;

		// Ignore the current and parent directory entries as well as any other hidden files or folders that may exist
		if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0 || *entry_name == '.') { continue; }

		const char *const fullpath = GetFullPath(path, entry_name);

		if (entry_type == DT_DIR)
		{
			ReadDirectory(fullpath, depth - 1);
		}
		else if (entry_type == DT_REG)
		{
			ReadFile(fullpath);
		}

		free(fullpath);
	}

	closedir(dir);
}

// Returns true if the directory handle is valid (not NULL) and false otherwise.
bool IsValidDirectory(DIR * dir)
{
	return dir != NULL;
}

// Defined in "FileReader.h".
bool IsValidDirectoryPath(const char *const path)
{
	DIR * dir = opendir(path);

	const bool is_path_valid = IsValidDirectory(dir);

	closedir(dir);

	return is_path_valid;
}

// Returns the full path resulting from a concatenation of the path and entry name variables.
// NOTE: This allocates memory on the heap which must be freed after use.
char * GetFullPath(const char *const path, const char *const entry_name)
{
	const unsigned int fullpath_length = strlen(path) + 1 + strlen(entry_name);
	char *const fullpath = malloc( fullpath_length * sizeof( *fullpath ) + 1 );

	strcpy(fullpath, path);
	strcat(fullpath, "/");
	strcat(fullpath, entry_name);
	*(fullpath + fullpath_length) = '\0';

	return fullpath;
}

// Reads a file specified by the path and processes it if it is a supported source file.
void ReadFile(const char *const path)
{
	FILE * file = fopen(path, "r");

	if (!IsValidFile(file))
	{
		fclose(file);
		return;
	}

	const char *const file_extension = GetFileExtension(path);

	if (IsFileExtension_JAVA(file_extension))
	{
		ReadFile_JAVA(file);
	}
	else if (IsFileExtension_C(file_extension))
	{
		ReadFile_C(file);
	}
	else if (IsFileExtension_CPP(file_extension))
	{
		ReadFile_CPP(file);
	}
	else if (IsFileExtension_HEADER(file_extension))
	{
		ReadFile_HEADER(file);
	}
	else if (IsFileExtension_CS(file_extension))
	{
		ReadFile_CS(file);
	}

	free(file_extension);

	fclose(file);
}

// Returns true if the file handle is valid (not NULL) and false otherwise.
bool IsValidFile(FILE * file)
{
	return file != NULL;
}

// Returns the extension of a file or an empty string if no extension exists.
// NOTE: This returns a string whose memory has been allocated on the heap and must be freed after use.
char * GetFileExtension(const char *const path)
{
	const int extension_index = StrFindBack(path, '.');

	if (extension_index == -1) { return EMPTY_STRING; }

	char *const extension = StrSubstr(path, extension_index + 1, strlen(path));
	StrToLowerCase(extension);

	return extension;
}

// Defined in "FileReader.h".
void DisplayStatistics(void)
{
	DisplayReaderStatistics();
}
