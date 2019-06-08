
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "Application/FileReader.h"
#include "Application/Extensions.h"
#include "Application/Readers.h"
#include "Utility/String.h"


// --- Function Prototypes --- //

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
void ReadDirectory(const char *const path)
{
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

		if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0) { continue; }
		if (*entry_name == '.') { continue; }

		const char *const fullpath = GetFullPath(path, entry_name);
		printf("[PATH] %s\n", fullpath);

		if (entry_type == DT_DIR)
		{
			ReadDirectory(fullpath);
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
	const unsigned int path_length = strlen(path);
	const unsigned int entry_name_length = strlen(entry_name);

	const unsigned int length = path_length + 1 + entry_name_length;

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
	FILE * file = fopen(path, "r");

	if (!IsValidFile(file))
	{
		fclose(file);
		return;
	}

	const char *const file_extension = GetFileExtension(path);
	printf("[FILE EXTENSION] = %s\n", file_extension);

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

	if (extension_index == -1) { return ""; }

	char *const extension = StrSubstr(path, extension_index + 1, strlen(path));
	StrToLowerCase(extension);

	return extension;
}

// Defined in "FileReader.h".
void DisplayStatistics(void)
{

}
