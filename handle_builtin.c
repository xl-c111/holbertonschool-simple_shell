#include <stdio.h>
#include <string.h>
#include "shell.h"

/**
 * handle_builtin - checks and hnadles built-in commands: exit and env
 * @argv: array of arguments strings
 *
 * Return: 1 if the built-in command is "exit" and shell should exit
 *         otherwise 0 (including built-in command "env" is executed)
 *
 */
int handle_builtin(char *argv[])
{
	int i;

	if (argv == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0)
		return (1);

	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (0);
	}
	return (0);
}
