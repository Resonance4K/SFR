
#ifndef SFR_READERS_H
#define SFR_READERS_H

#include <stdio.h>

// Initializes the properties of the readers.
void InitReaders(void);

// Reads a source file that is written in Java.
void ReadFile_JAVA(FILE * file);

// Reads a source file that is written in C.
void ReadFile_C(FILE * file);

// Reads a source file that is written in C++.
void ReadFile_CPP(FILE * file);

// Reads a header file that is written in C/C++.
void ReadFile_HEADER(FILE * file);

// Reads a source file that is written in C#.
void ReadFile_CS(FILE * file);

// Displays the statistics of the files that the readers have read.
void DisplayReaderStatistics(void);

#endif
