
#ifndef SFR_READERS_H
#define SFR_READERS_H


#include <stdio.h>


// --- Constant Definitions --- //

#define TOTAL_FILES_SUPPORTED    5


// Structure that stores statistical information about the files being read.
struct FILE_DATA
{
	const char * file_type;
	unsigned long code_lines;
	unsigned long empty_lines;
	unsigned long doc_lines;
	unsigned long file_count;
};

// Array to store the file data information for each file type.
extern struct FILE_DATA data[];

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


#endif
