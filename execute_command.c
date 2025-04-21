#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"


/**
 * execute_command - execute a command using execve that prints an error
 *                   message and exits if the command fails
 * @argv: a pointer to an array of strings
 */
void execute_command(char *const argv[])
{
	if (execve(argv[0], argv, environ) == -1)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
}
