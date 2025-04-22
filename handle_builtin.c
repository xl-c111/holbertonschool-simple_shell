#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
/**
 * handle_builtin - checks and hnadles built-in commands: exit and env
 * @argv: array of argument strings(parsed from user input)
 * @line: input buffer to be freed if "exit" is called
 * @last_status: exit code to use if "exit" is called
 * Return: 1 if the built-in command is handled
 *         otherwise 0
 */
int handle_builtin(char *argv[], char *line, int last_status)
{
	int i;

	if (argv == NULL || argv[0] == NULL)
		return (0);
	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(last_status);
	}
	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (1);
	}
	return (0);
}


