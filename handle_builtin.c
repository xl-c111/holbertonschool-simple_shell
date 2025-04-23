#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
/**
 * handle_builtin - checks and hnadles built-in commands: exit and env
 * @argv: array of argument strings(parsed from user input)
 * @line: the original input line(needs to be freed if exiting)
 * @last_status: exit code to use if exiting
 * Return: 1 if the built-in command is handled
 *         otherwise 0
 *
 * Description: - argv[0] is used to check if user input nothing, like pressing ENTER or typing only spaces
 *              - strcmp(argv[0], 'exit') to check if the command name is exit
 *              - exit(last_status) exits the entire program immediately; return(last_status) returns from the current function
 */
int handle_builtin(char *argv[], char *line, int last_status)
{
	int i;

	if (argv == NULL || argv[0] == NULL) /* argv is from parse_line */
		return (0);
	if (strcmp(argv[0], "exit") == 0)    /* check if the command name is 'exit' */
	{
		free(line);
		exit(last_status);           /* exit() terminates the entire program */
	}
	if (strcmp(argv[0], "env") == 0)    /* check if the command name is 'env' */
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (1);
	}
	return (0);
}


