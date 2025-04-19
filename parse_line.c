#include <string.h>
#include "shell.h"

/**
 * parse_line - extracts only the first word(command) from input
 * @line: input buffer (modified in place)
 * @argv: output array,  should have room for at least 2 pointers
 * Return: number of tokens (0, 1)
 */
int parse_line(char *line, char *argv[])
{
	int count = 0;
	char *token;

	token = strtok(line, " \t");
	if (token != NULL)
	{
		argv[count++] = token;
	}

	argv[count] = NULL;
	return (count);
}
