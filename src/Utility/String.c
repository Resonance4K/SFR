
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
