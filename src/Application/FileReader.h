
#ifndef SFR_FILEREADER_H
#define SFR_FILEREADER_H


// Reads the root directory specified by the path that is provided by the user from the argument vector.
void ReadRootDirectory(const char *const path);

// Displays the statistics of all supported source files that were read from the provided root directory.
void DisplayStatistics(void);


#endif
