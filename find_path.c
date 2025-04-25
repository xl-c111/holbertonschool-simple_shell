#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include <errno.h>
/**
 * find_path - find executable file for a given command in the
 *             directories listed in PATH
 * @command: pointer to the command-line argument (from parsed tokens, argv[0] is passed to find_path)
 * Return: a pointer to string containing fullpath to the executable
 *         or NULL if no command found or an error occurs
 *
 * Description: - validate command 
 *              - strchr(command, '/') to check if user already gave a path, 
 *                           if command contains a ‘/’, means user input a full or relative path, so don't need to search in PATH
 *              - _getenv to get the PATH environment variable 
 *              - strdup() to get a copy_path for modifying
 *              - strtok() plit the PATH by colon to get each directory
 *
 */
char *find_path(const char *command)
{
	char *env_path;      /* to store the PATH env variable*/
	char *copy_path;     /* to store a modifiable copy */
	char *token;         /* to store each directory split from PATH by strtok */
	char *fullpath;      /* to store the full path */

	if (command == NULL || *command == '\0')  /* if command is NULL or empty */
		return (NULL);

	if (strchr(command, '/'))             /* check if user already gave a path, in this case, skip searching in PATH */
	{
		if (access(command, X_OK) == 0)        /* check if it's executable */
			return (strdup(command));      /* if so, returns a modifiable copy */
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		return (NULL);
	}
	env_path = _getenv("PATH");                   /* get the value of the PATH environment variable */
	if (env_path == NULL || *env_path == '\0')    /* if PATH does not exits, or is empty */
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		return (NULL);
	}
	copy_path = strdup(env_path);
	if (copy_path == NULL)
	{
		perror("strdup");              /* if strdup fails, print error and return NULL */
		return (NULL);
	}
	token = strtok(copy_path, ":");       /* split the PATH by colon to get individual directory */
	while (token != NULL)                 
	{
		fullpath = build_full_path(token, command);     /* loop through each direcroty, try to construct a full path */

		if (fullpath)                /* if a full path is found and executable */
		{
			free(copy_path);
			return (fullpath);
		}
		token = strtok(NULL, ":");          /* moves to the next directory */
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", command);
	free(copy_path);
	return (NULL);
}
