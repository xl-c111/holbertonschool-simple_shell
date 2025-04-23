#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
/**
 * build_full_path - constructs a full path to a command in a given directory
 * @dir: directory (folder path) to look in(dir is from strtok(copy_path, ":"))
 * @command: name of executable file
 *
 * Return: the complete path is it's executable, otherwise NULL
 *
 * Description: - combines each directory with the first token of user input(command name) to get the full path
 *              - check if the file at the full path is executable
 *
 */
char *build_full_path(const char *dir, const char *command)
{
	char *fullpath;      /* a ptr to the new path string */
	size_t len;          /* length of combined path */

       	len = strlen(dir) + strlen(command) + 2;     /* one for slash between directory and command, one for '\0' */
	fullpath = malloc(len);

	if (fullpath == NULL)
		return (NULL);

	snprintf(fullpath, len, "%s/%s", dir, command);     /* format the string dir/command into the allocated memory */

	if (access(fullpath, X_OK) == 0)      /* check if the file at the fullpath is executable */
		return (fullpath);

	free(fullpath);
	return (NULL);
}
