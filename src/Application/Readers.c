
#include "Application/Readers.h"


// --- Constant Definitions --- //

#define MAX_LINE_LENGTH    512

#define JAVA        0
#define C           1
#define CPP         2
#define HEADER      3
#define CS          4


// Defined in "Readers.h".
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
		data[i].code_lines = 0;
		data[i].empty_lines = 0;
		data[i].doc_lines = 0;
		data[i].file_count = 0;
	}
}

// Defined in "Readers.h".
void ReadFile_JAVA(FILE * file)
{

}

// Defined in "Readers.h".
void ReadFile_C(FILE * file)
{

}

// Defined in "Readers.h".
void ReadFile_CPP(FILE * file)
{

}

// Defined in "Readers.h".
void ReadFile_HEADER(FILE * file)
{

}

// Defined in "Readers.h".
void ReadFile_CS(FILE * file)
{

}
