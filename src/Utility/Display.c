
#include <stdio.h>
#include <string.h>



// Defined in "Display.h".
void DisplayDivider(const char c, const unsigned int length)
{
	for (unsigned int i = 0; i < length; i++)
	{
		printf("%c", c);
	}

	printf("\n");
}

// Defined in "Display.h".
void DisplayDefaultDivider(const unsigned int length)
{
	DisplayDivider('-', length);
}

// Defined in "Display.h".
void DisplayWhitespace(const unsigned int length)
{
	for (unsigned int i = 0; i < length; i++)
	{
		printf("%c", ' ');
	}
}

// Defined in "Display.h".
void DisplayStrWithPadding(const char *const str, const unsigned int width)
{
	const unsigned int length = strlen(str);

	printf("%s", str);

	if (length < width)
	{
		DisplayWhitespace(width - length);
	}
}

// Defined in "Display.h".
void DisplayNumberWithPadding(const unsigned long number, const unsigned int width)
{
	char str[16];

	// The "%u" specifier represents an unsigned decimal integer
	snprintf(str, 16, "%u", number);
	
	DisplayStrWithPadding(str, width);
}
