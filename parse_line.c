#include <string.h>
#include "shell.h"

/**
 * parse_line - trim whitespace and split into command + optional arg
 * @line: input buffer (modified in place)
 * @argv: out array, must have room for at least 3 pointers
 * Return: number of tokens (0, 1 or 2)
 */
int parse_line(char *line, char *argv[])
{
	int count = 0;
	char *token;

	token = strtok(line, " \t");
	if (token != NULL)
	{
		argv[count++] = token;

		token = strtok(NULL, " \t");
		if (token != NULL)
			argv[count++] = token;
	}

	argv[count] = NULL;
	return (count);
}
