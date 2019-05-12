
#include <stdlib.h>
#include <string.h>

#include "Utility/String.h"


// Defined in "String.h".
void StrReplaceAll(char *const string, const char target, const char replacement)
{
	unsigned int index = 0;

	while (*(string + index) != '\0')
	{
		if (*(string + index) == target)
		{
			*(string + index) = replacement;
		}

		index++;
	}
}

// Defined in "String.h".
void StrToLowerCase(char *const string)
{
	unsigned int index = 0;

	while (*(string + index) != '\0')
	{
		const unsigned int cInt = (unsigned int) *(string + index);
		const unsigned int cOffset = (unsigned int) ('a' - 'A');

		if (cInt >= 'A' && cInt <= 'Z')
		{
			*(string + index) = (char) (cInt + cOffset);
		}

		index++;
	}
}

// Defined in "String.h".
void StrToUpperCase(char *const string)
{
	unsigned int index = 0;

	while (*(string + index) != '\0')
	{
		const unsigned int cInt = (unsigned int) *(string + index);
		const unsigned int cOffset = (unsigned int) ('a' - 'A');

		if (cInt >= 'a' && cInt <= 'z')
		{
			*(string + index) = (char) (cInt - cOffset);
		}

		index++;
	}
}

// Defined in "String.h".
int StrFindFront(const char *const string, const char target)
{
	for (unsigned int i = 0; i < strlen(string); i++)
	{
		if (*(string + i) == target)
		{
			return i;
		}
	}

	return -1;
}

// Defined in "String.h".
int StrFindBack(const char *const string, const char target)
{
	for (int i = (strlen(string) - 1); i >= 0; i--)
	{
		if (*(string + i) == target)
		{
			return i;
		}
	}

	return -1;
}

// Defined in "String.h".
char * StrSubstr(const char *const string, const unsigned int start, const unsigned int end)
{
	if (end < start) { return NULL; }
	if (start > (strlen(string) - 1)) { return NULL; }

	const unsigned int substr_length = (end > strlen(string) ? (strlen(string) - start) : (end - start));

	char *const substr = malloc( substr_length * sizeof( *substr ) + 1 );

	for (unsigned int i = 0; i < substr_length; i++)
	{
		*(substr + i) = *(string + start + i);
	}
	*(substr + substr_length) = '\0';

	return substr;
}
