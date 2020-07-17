
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "Application/Readers.h"
#include "Utility/String.h"
#include "Utility/Display.h"



void ReadFile_GENERIC(FILE * file, const unsigned int file_type);

bool ProcessBlankLine(const char *const line, const unsigned int file_type);
bool ProcessCommentLine(const char *const line, const unsigned int file_type);
void ProcessPhysicalLine(const unsigned int file_type);
void IncrementFileCount(const unsigned int file_type);

void DisplayDataEntry(const unsigned int index, const unsigned int *const column_widths);

void CalculateDataTotals(void);
unsigned int * CalculateColumnWidths(void);
unsigned int CalculateTotalTableWidth(const unsigned int *const column_widths);
unsigned int CalculateNumberLength(const unsigned long number);

bool IsEOF(FILE * file);
char * GetLine(FILE * file);



#define STAT_NUMBER_LIMIT        50000000UL

#define TOTAL_FILES_SUPPORTED    5
#define TOTAL_STATS_SUPPORTED    6

#define TOTALS        0
#define JAVA          1
#define C             2
#define CPP           3
#define HEADER        4
#define CS            5



// Structure that stores statistical information about the files being read.
struct FILE_DATA
{
	const char * file_type;
	unsigned long physical_lines;
	unsigned long blank_lines;
	unsigned long comment_lines;
	unsigned long total_lines;
	unsigned long file_count;
};

// Array to store the file data information for each file type.
struct FILE_DATA data[TOTAL_FILES_SUPPORTED + 1];

// Array that stores the names of the recorded statistics.
char * stat_names[TOTAL_STATS_SUPPORTED] =
{
	"",
	"Physical Lines",
	"Blank Lines",
	"Comment Lines",
	"Total Lines",
	"File Count"
};

// Defined in "Readers.h".
void InitReaders(void)
{
	data[TOTALS] = (struct FILE_DATA) { "Total",        0UL, 0UL, 0UL, 0UL, 0UL };

	data[JAVA]   = (struct FILE_DATA) { "Java",         0UL, 0UL, 0UL, 0UL, 0UL };
	data[C]      = (struct FILE_DATA) { "C",            0UL, 0UL, 0UL, 0UL, 0UL };
	data[CPP]    = (struct FILE_DATA) { "C++",          0UL, 0UL, 0UL, 0UL, 0UL };
	data[HEADER] = (struct FILE_DATA) { "C/C++ Header", 0UL, 0UL, 0UL, 0UL, 0UL };
	data[CS]     = (struct FILE_DATA) { "C#",           0UL, 0UL, 0UL, 0UL, 0UL };
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
		if (data[file_type].blank_lines < STAT_NUMBER_LIMIT)
		{
			data[file_type].blank_lines++;
			data[file_type].total_lines++;
		}

		return true;
	}

	return false;
}

// Returns true if the line read from the file has successfully been processed as a comment line.
bool ProcessCommentLine(const char *const line, const unsigned int file_type)
{
	if (StrStartsWith(line, 4, "//", "/*", "*", "*/"))
	{
		if (data[file_type].comment_lines < STAT_NUMBER_LIMIT)
		{
			data[file_type].comment_lines++;
			data[file_type].total_lines++;
		}

		return true;
	}

	return false;
}

// Processes a line read from the file as a physical line.
void ProcessPhysicalLine(const unsigned int file_type)
{
	if (data[file_type].physical_lines < STAT_NUMBER_LIMIT)
	{
		data[file_type].physical_lines++;
		data[file_type].total_lines++;
	}
}

// Increments the file count after a file has been fully processed.
void IncrementFileCount(const unsigned int file_type)
{
	if (data[file_type].file_count < STAT_NUMBER_LIMIT)
	{
		data[file_type].file_count++;
	}
}

// Defined in "Readers.h".
void DisplayReaderStatistics(void)
{
	CalculateDataTotals();

	const unsigned int *const column_widths = CalculateColumnWidths();
	const unsigned int table_width = CalculateTotalTableWidth(column_widths);

	printf("\n");
	DisplayDefaultDivider(table_width);
	printf("\n");

	for (unsigned int i = 0; i < TOTAL_STATS_SUPPORTED; i++)
	{
		DisplayStrWithPadding(*(stat_names + i), *(column_widths + i));
	}

	printf("\n");
	DisplayDefaultDivider(table_width);
	printf("\n");

	for (unsigned int i = 1; i < TOTAL_FILES_SUPPORTED + 1; i++)
	{
		if (data[i].file_count == 0) { continue; }

		DisplayDataEntry(i, column_widths);
		printf("\n");
	}

	DisplayDefaultDivider(table_width);
	printf("\n");
	DisplayDataEntry(TOTALS, column_widths);
	printf("\n");
	DisplayDefaultDivider(table_width);
	printf("\n");

	free(column_widths);
}

// Displays the data entry at the specified index.
void DisplayDataEntry(const unsigned int index, const unsigned int *const column_widths)
{
	DisplayStrWithPadding(data[index].file_type, *column_widths);
	DisplayNumberWithPadding(data[index].physical_lines, *(column_widths + 1));
	DisplayNumberWithPadding(data[index].blank_lines, *(column_widths + 2));
	DisplayNumberWithPadding(data[index].comment_lines, *(column_widths + 3));
	DisplayNumberWithPadding(data[index].total_lines, *(column_widths + 4));
	DisplayNumberWithPadding(data[index].file_count, *(column_widths + 5));
}

// Calculates the totals of the file data information for each statistic for all file types.
void CalculateDataTotals(void)
{
	for (unsigned int i = 1; i < TOTAL_FILES_SUPPORTED + 1; i++)
	{
		data[TOTALS].physical_lines += data[i].physical_lines;
		data[TOTALS].blank_lines += data[i].blank_lines;
		data[TOTALS].comment_lines += data[i].comment_lines;
		data[TOTALS].total_lines += data[i].total_lines;
		data[TOTALS].file_count += data[i].file_count;
	}
}

// Returns an array of calculated optimal column widths for the recorded statistics.
// NOTE: This allocates memory on the heap which must be freed after use.
unsigned int * CalculateColumnWidths(void)
{
	unsigned int *const column_widths = malloc( TOTAL_STATS_SUPPORTED * sizeof( *column_widths ) );

	// Set initial column width to equal the length of the column name
	for (unsigned int i = 0; i < TOTAL_STATS_SUPPORTED; i++)
	{
		*(column_widths + i) = strlen(*(stat_names + i));
	}

	// Calculate the File Type column width
	for (unsigned int i = 0; i < TOTAL_FILES_SUPPORTED + 1; i++)
	{
		const unsigned int file_type_width = strlen(data[i].file_type);
		if (file_type_width > *column_widths)
		{
			*column_widths = file_type_width;
		}
	}

	// Calculate the Physical Lines column width
	const unsigned int physical_line_width = CalculateNumberLength(data[TOTALS].physical_lines);
	if (physical_line_width > *(column_widths + 1))
	{
		*(column_widths + 1) = physical_line_width;
	}

	// Calculate the Blank Lines column width
	const unsigned int blank_line_width = CalculateNumberLength(data[TOTALS].blank_lines);
	if (blank_line_width > *(column_widths + 2))
	{
		*(column_widths + 2) = blank_line_width;
	}

	// Calculate the Comment Lines column width
	const unsigned int comment_line_width = CalculateNumberLength(data[TOTALS].comment_lines);
	if (comment_line_width > *(column_widths + 3))
	{
		*(column_widths + 3) = comment_line_width;
	}

	// Calculate the Total Lines column width
	const unsigned int total_line_width = CalculateNumberLength(data[TOTALS].total_lines);
	if (total_line_width > *(column_widths + 4))
	{
		*(column_widths + 4) = total_line_width;
	}

	// Calculate the File Count column width
	const unsigned int file_count_width = CalculateNumberLength(data[TOTALS].file_count);
	if (file_count_width > *(column_widths + 5))
	{
		*(column_widths + 5) = file_count_width;
	}

	// Add padding on the right side of the columns to increase readability
	const unsigned int column_padding = 3;
	for (unsigned int i = 0; i < TOTAL_STATS_SUPPORTED; i++)
	{
		*(column_widths + i) += column_padding;
	}

	return column_widths;
}

// Returns the total sum of all column widths.
unsigned int CalculateTotalTableWidth(const unsigned int *const column_widths)
{
	unsigned int total_width = 0;

	for (unsigned int i = 0; i < TOTAL_STATS_SUPPORTED; i++)
	{
		total_width += column_widths[i];
	}

	return total_width;
}

// Calculates the amount of digits in the number.
unsigned int CalculateNumberLength(const unsigned long number)
{
	return (number > 0 ? log10(number) + 1 : 1);
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
		// Stop processing when the LF line ending character is found
		if (cInt == '\n') { break; }
		// Skip processing when the CR line ending character is found
		if (cInt == '\r') { continue; }

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
