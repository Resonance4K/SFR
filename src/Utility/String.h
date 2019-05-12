
#ifndef SFR_STRING_H
#define SFR_STRING_H


// Modifies the string by replacing all target characters with the replacement character.
void StrReplaceAll(char *const string, const char target, const char replacement);

// Modifies the string by turning all uppercase characters into lowercase characters.
void StrToLowerCase(char *const string);

// Modifies the string by turning all lowercase characters into uppercase characters.
void StrToUpperCase(char *const string);

// Searches the string from start to end in order to find the target character.
// Returns the index of the target character or -1 if the target character could not be found.
int StrFindFront(const char *const string, const char target);

// Searches the string from end to start in order to find the target character.
// Returns the index of the target character or -1 if the target character could not be found.
int StrFindBack(const char *const string, const char target);

// Extracts the characters of the string between the start index (inclusive) and end index (exclusive).
// Returns a substring of the string or NULL if there is no valid substring.
// NOTE: This allocates memory on the heap which must be freed after use.
char * StrSubstr(const char *const string, const unsigned int start, const unsigned int end);


#endif
