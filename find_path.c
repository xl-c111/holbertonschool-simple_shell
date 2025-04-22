#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include <errno.h>
/**
 * find_path - find executable file for a given command in the
 *             directories listed in PATH
 * @command: pointer to the command-line argument
 *
 * Return: a pointer to string containing fullpath to the executable
 *         ot NULL if no command found or an error occurs
 */
char *find_path(const char *command)
{
	char *env_path, *copy_path, *token, *fullpath;
	size_t len;

	if (command == NULL || *command == '\0')
		return (NULL);

	if (strchr(command, '/'))
		return (access(command, X_OK) == 0 ? strdup(command) : NULL);

	env_path = _getenv("PATH");
	copy_path = strdup(env_path);
	if (env_path == NULL || copy_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		free(copy_path);
		return (NULL);
	}
	token = strtok(copy_path, ":");
	while (token != NULL)
	{
		len = strlen(token) + strlen(command) + 2;
		fullpath = malloc(len);

		if (fullpath == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		snprintf(fullpath, len, "%s/%s", token, command);

		if (access(fullpath, X_OK) == 0)
		{
			free(copy_path);
			return (fullpath);
		}
		free(fullpath);
		token = strtok(NULL, ":");
	}
	free(copy_path);
	return (NULL);
}
