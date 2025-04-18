#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"


/**
 * execute_command - utility for execve that prints an error if exec fails
 * @argv: a poniter to array of string
 */
void execute_command(char *const argv[])
{
	if (execve(argv[0], argv, environ) == -1)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
}
