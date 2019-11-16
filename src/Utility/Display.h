
#ifndef SFR_DISPLAY_H
#define SFR_DISPLAY_H

// Displays a divider consisting of the specified character up to the specified length.
void DisplayDivider(const char c, const unsigned int length);

// Displays a divider consisting of a default character up to the specified length.
void DisplayDefaultDivider(const unsigned int length);

// Displays a number of whitespace characters up to the specified length.
void DisplayWhitespace(const unsigned int length);

// Displays a string with whitespace padding if the length is less than the width specified.
void DisplayStrWithPadding(const char *const str, const unsigned int width);

// Displays a number with whitespace padding if the length is less than the width specified.
void DisplayNumberWithPadding(const unsigned long number, const unsigned int width);

#endif
