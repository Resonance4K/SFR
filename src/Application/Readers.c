
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Application/Readers.h"
#include "Utility/String.h"


// --- Function Prototypes ---//

void ReadFile_GENERIC(FILE * file, const unsigned int file_type);

bool ProcessBlankLine(const char *const line, const unsigned int file_type);
bool ProcessCommentLine(const char *const line, const unsigned int file_type);
void ProcessPhysicalLine(const unsigned int file_type);
void IncrementFileCount(const unsigned int file_type);

bool IsEOF(FILE * file);
char * GetLine(FILE * file);


// --- Constant Definitions --- //

#define TOTAL_FILES_SUPPORTED    5

#define JAVA        0
#define C           1
#define CPP         2
#define HEADER      3
#define CS          4


// Structure that stores statistical information about the files being read.
struct FILE_DATA
{
	const char * file_type;
	unsigned long physical_lines;
	unsigned long blank_lines;
	unsigned long comment_lines;
	unsigned long file_count;
};

// Array to store the file data information for each file type.
struct FILE_DATA data[TOTAL_FILES_SUPPORTED];

// Defined in "Readers.h".
void InitReaders(void)
{
	data[JAVA].file_type = "Java";
	data[C].file_type = "C";
	data[CPP].file_type = "C++";
	data[HEADER].file_type = "C/C++ Header";
	data[CS].file_type = "C#";

	for (int i = 0; i < TOTAL_FILES_SUPPORTED; i++)
	{
		data[i].physical_lines = 0;
		data[i].blank_lines = 0;
		data[i].comment_lines = 0;
		data[i].file_count = 0;
	}
}

// Defined in "Readers.h".
void ReadFile_JAVA(FILE * file)
{
	ReadFile_GENERIC(file, JAVA);
}

// Defined in "Readers.h".
void ReadFile_C(FILE * file)
{
	ReadFile_GENERIC(file, C);
}

// Defined in "Readers.h".
void ReadFile_CPP(FILE * file)
{
	ReadFile_GENERIC(file, CPP);
}

// Defined in "Readers.h".
void ReadFile_HEADER(FILE * file)
{
	ReadFile_GENERIC(file, HEADER);
}

// Defined in "Readers.h".
void ReadFile_CS(FILE * file)
{
	ReadFile_GENERIC(file, CS);
}

// Generic function to handle file reading and line processing logic.
void ReadFile_GENERIC(FILE * file, const unsigned int file_type)
{
	while (!IsEOF(file))
	{
		const char *const line = GetLine(file);

		const bool blank_line = ProcessBlankLine(line, file_type);
		const bool comment_line = ProcessCommentLine(line, file_type);

		if (!blank_line && !comment_line)
		{
			ProcessPhysicalLine(file_type);
		}

		free(line);
	}

	IncrementFileCount(file_type);
}

// Returns true if the line read from the file has successfully been processed as a blank line.
bool ProcessBlankLine(const char *const line, const unsigned int file_type)
{
	if (*line == '\0')
	{
		data[file_type].blank_lines++;
		return true;
	}

	return false;
}

// Returns true if the line read from the file has successfully been processed as a comment line.
bool ProcessCommentLine(const char *const line, const unsigned int file_type)
{
	if (StrStartsWith(line, 4, "//", "/*", "*", "*/"))
	{
		data[file_type].comment_lines++;
		return true;
	}

	return false;
}

// Processes a line read from the file as a physical line.
void ProcessPhysicalLine(const unsigned int file_type)
{
	data[file_type].physical_lines++;
}

// Increments the file count after a file has been fully processed.
void IncrementFileCount(const unsigned int file_type)
{
	data[file_type].file_count++;
}

// Defined in "Readers.h".
void DisplayReaderStatistics(void)
{
	for (unsigned int i = 0; i < TOTAL_FILES_SUPPORTED; i++)
	{
		if (data[i].file_count == 0) { continue; }

		printf("File Type = %s\n", data[i].file_type);
		printf("Physical Lines = %d\n", data[i].physical_lines);
		printf("Blank Lines = %d\n", data[i].blank_lines);
		printf("Comment Lines = %d\n", data[i].comment_lines);
		printf("File Count = %d\n", data[i].file_count);
		printf("\n");
	}
}

// Returns true if the file has been fully processed.
bool IsEOF(FILE * file)
{
	fpos_t position;
	fgetpos(file, &position);

	const bool is_eof = (fgetc(file) == EOF);

	fsetpos(file, &position);

	return is_eof;
}

// Returns a line from a file with leading whitespace removed.
// NOTE: This allocates memory on the heap which must be freed after use.
char * GetLine(FILE * file)
{
	int cInt = 0;
	unsigned int length = 1;
	bool leading_whitespace_processed = false;

	char * line = malloc( length * sizeof( *line ) );

	while ((cInt = fgetc(file)) != EOF)
	{
		if (cInt == '\n' || cInt == '\r') { break; }

		if (!leading_whitespace_processed)
		{
			if (cInt == ' ' || cInt == '\t') { continue; }
			leading_whitespace_processed = true;
		}

		*(line + length - 1) = (char) cInt;

		char * temp_line = realloc( line, length + 1 );

		if (temp_line != NULL)
		{
			line = temp_line;
			length++;
		}
	}

	*(line + length - 1) = '\0';

	return line;
}
