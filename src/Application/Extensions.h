
#ifndef SFR_EXTENSIONS_H
#define SFR_EXTENSIONS_H

#include <stdbool.h>

// Returns true if the specified extension is a Java extension and false otherwise.
bool IsFileExtension_JAVA(const char *const extension);

// Returns true if the specified extension is a C extension and false otherwise.
bool IsFileExtension_C(const char *const extension);

// Returns true if the specified extension is a C++ extension and false otherwise.
bool IsFileExtension_CPP(const char *const extension);

// Returns true if the specified extension is a C/C++ Header extension and false otherwise.
bool IsFileExtension_HEADER(const char *const extension);

// Returns true if the specified extension is a C# extension and false otherwise.
bool IsFileExtension_CS(const char *const extension);

#endif
