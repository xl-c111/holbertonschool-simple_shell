#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
/**
 * build_full_path - constructs a full path to a command in a given directory
 * @dir: directory to look in
 * @command: name of the executable file
 *
 * Return: the complete path if it's executable, otherwise NULL
 */
char *build_full_path(const char *dir, const char *command)
{
	char *fullpath;
	size_t len;

       	len = strlen(dir) + strlen(command) + 2;
	fullpath = malloc(len);

	if (fullpath == NULL)
		return (NULL);

	snprintf(fullpath, len, "%s/%s", dir, command);

	if (access(fullpath, X_OK) == 0)
		return (fullpath);

	free(fullpath);
	return (NULL);
}
