#include <string.h>
#include "shell.h"

/**
 * parse_line - parse the input line into command and its arguments
 * @line: input buffer (modified in place)
 * @argv: output array,  should have space for at least MAX_ARGS pointers
 * Return: number of tokens parsed
 *         0 if line is empty or contains only whitespace
 */
int parse_line(char *line, char *argv[])
{
	int count = 0;
	char *token;

	token = strtok(line, " \t");
	while (token != NULL && count <  MAX_ARGS - 1)
	{
		argv[count++] = token;
		token = strtok(NULL, " \t");
	}

	argv[count] = NULL;
	return (count);
}
