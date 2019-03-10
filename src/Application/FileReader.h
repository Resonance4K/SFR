
#ifndef SFR_FILEREADER_H
#define SFR_FILEREADER_H


#include <stdio.h>
#include <dirent.h>


void ReadDirectory(const char *const path);
DIR * GetDirectory(const char *const path);

void ReadFile(const char *const path);
FILE * GetFile(const char *const path, const char *const mode);

void DisplayStatistics();


#endif
