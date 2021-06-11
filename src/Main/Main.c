
#include <stdio.h>
#include <stdlib.h>

#include "Application/SFR.h"



// The entry point of the program executed by the Operating System (OS).
int main(int argc, char ** argv)
{
	const int program_status = (SourceFileReader(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE);

	printf("\n");
	printf("Program terminated with status: %s\n", (program_status == EXIT_SUCCESS ? "SUCCESS" : "FAILURE"));
	printf("\n");

	return program_status;
}
