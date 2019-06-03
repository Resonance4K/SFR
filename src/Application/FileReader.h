
#ifndef SFR_FILEREADER_H
#define SFR_FILEREADER_H


#include <stdbool.h>


// Initializes the properties of the file reader.
void InitFileReader(void);

// Reads the directory specified by the path and processes its contents.
void ReadDirectory(const char *const path);

// Returns true if the directory path is valid and false otherwise.
bool IsValidDirectoryPath(const char *const path);

// Displays the statistics of all supported source files that were read.
void DisplayStatistics(void);


#endif
