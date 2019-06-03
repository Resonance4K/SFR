
#include <string.h>

#include "Application/Extensions.h"


// Defined in "Extensions.h".
bool IsFileExtension_JAVA(const char *const extension)
{
	return strcmp(extension, "java") == 0;
}

// Defined in "Extensions.h".
bool IsFileExtension_C(const char *const extension)
{
	return strcmp(extension, "c") == 0;
}

// Defined in "Extensions.h".
bool IsFileExtension_CPP(const char *const extension)
{
	return strcmp(extension, "cpp") == 0;
}

// Defined in "Extensions.h".
bool IsFileExtension_HEADER(const char *const extension)
{
	return strcmp(extension, "h") == 0;
}

// Defined in "Extensions.h".
bool IsFileExtension_CS(const char *const extension)
{
	return strcmp(extension, "cs") == 0;
}
