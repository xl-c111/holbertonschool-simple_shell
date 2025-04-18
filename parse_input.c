#include <string.h>
#include "shell.h"

/**
 * parse_input - trim whitespace and split into command + optional arg
 * @line: input buffer (modified in place)
 * @argv: out array, must have room for at least 3 pointers
 * Return: number of tokens (0, 1 or 2)
 */
int parse_input(char *line, char *argv[])
{
	char *cmd = line;
	char *end;
	char *p;
	char *end2;
	int count = 0;

	while (*cmd == ' ' || *cmd == '\t')
		cmd++;

	if (*cmd == '\0')
		return (0);

	end = cmd + strlen(cmd) - 1;
	while (end > cmd && (*end == ' ' || *end == '\t'))
		*end-- = '\0';

	argv[0] = cmd;
	count = 1;

	p = cmd;
	while (*p && *p != ' ' && *p != '\t')
		p++;

	if (*p)
	{
		*p++ = '\0';

		while (*p == ' ' || *p == '\t')
			p++;
		if (*p)
		{
			argv[1] = p;
			count = 2;
			end2 = p + strlen(p) - 1;
			while (end2 > p && (*end2 == ' ' || *end2 == '\t'))
				*end2-- = '\0';
		}
	}
	argv[count] = NULL;
	return (count);
}


