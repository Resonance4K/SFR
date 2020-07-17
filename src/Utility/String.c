
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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
	if (end < start) { return EMPTY_STRING; }
	if (start > (strlen(string) - 1)) { return EMPTY_STRING; }

	const unsigned int substr_length = (end > strlen(string) ? (strlen(string) - start) : (end - start));

	char *const substr = malloc( substr_length * sizeof( *substr ) + 1 );

	for (unsigned int i = 0; i < substr_length; i++)
	{
		*(substr + i) = *(string + start + i);
	}
	*(substr + substr_length) = '\0';

	return substr;
}

// Defined in "String.h".
bool StrStartsWith(const char *const string, const unsigned int count, ...)
{
	va_list args;
	va_start(args, count);

	bool result = false;
	unsigned int index = 0;

	while (index < count)
	{
		const char *const target = va_arg(args, char *);
		const char *const substr_pointer = strstr(string, target);

		if (substr_pointer != NULL && substr_pointer == string)
		{
			result = true;
			break;
		}

		index++;
	}

	va_end(args);

	return result;
}

// Defined in "String.h".
int * StrToInt(const char *const string)
{
	int *const result = malloc( sizeof( *result ) );
	*result = 0;

	unsigned int index = 0;

	while (*(string + index) != '\0')
	{
		// Prevent the string from being converted into a number if any character is not a valid number
		if (*(string + index) < '0' || *(string + index) > '9')
		{
			return NULL;
		}

		const unsigned int number = (unsigned int) (*(string + index) - '0');
		*result = (*result * 10) + number;

		index++;
	}

	return result;
}
