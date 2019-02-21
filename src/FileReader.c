
#include "FileReader.h"


void ReadDirectory(const char *const path)
{
	DIR * dir = GetDirectory(path);

	if (dir == NULL) { return; }

	struct dirent * ent;
	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) { continue; }

		printf("%s\n", ent->d_name);
	}

	closedir(dir);
}

DIR * GetDirectory(const char *const path)
{
	return opendir(path);
}

void ReadFile(const char *const path)
{
	FILE * file = GetFile(path, "r");
}

FILE * GetFile(const char *const path, const char *const mode)
{
	return fopen(path, mode);
}

void DisplayStatistics()
{

}
