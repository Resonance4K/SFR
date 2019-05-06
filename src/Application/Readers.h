
#ifndef SFR_READERS_H
#define SFR_READERS_H


#include <stdio.h>


// Reads a source file that is written in Java.
void ReadFile_JAVA(FILE * file);

// Reads a source file that is written in C.
void ReadFile_C(FILE * file);

// Reads a source file that is written in C++.
void ReadFile_CPP(FILE * file);

// Reads a header file that is written in C/C++.
void ReadFile_HEADER(FILE * file);


#endif
