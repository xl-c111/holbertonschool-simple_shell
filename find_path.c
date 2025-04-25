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
 * Return: a pointer to string containing fullpath to the executable
 *         or NULL if no command found or an error occurs
 */
char *find_path(const char *command)
{
	char *env_path, *copy_path, *token, *fullpath;

	if (command == NULL || *command == '\0')
		return (NULL);

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		return (NULL);
	}
	env_path = _getenv("PATH");
	if (env_path == NULL || *env_path == '\0')
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		return (NULL);
	}
	copy_path = strdup(env_path);
	if (copy_path == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	token = strtok(copy_path, ":");
	while (token != NULL)
	{
		fullpath = build_full_path(token, command);

		if (fullpath)
		{
			free(copy_path);
			return (fullpath);
		}
		token = strtok(NULL, ":");
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", command);
	free(copy_path);
	return (NULL);
}
