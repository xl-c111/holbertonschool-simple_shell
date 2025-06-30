#include <string.h>
#include "shell.h"

/**
 * parse_input - trim whitespace and split into command + optional arg
 * @line: input buffer (modified in place)
 * @argv: out array, must have room for at least 3 pointers
 * Return: number of tokens (0, 1 or 2)
 * Description: - trim the leading whitespace:  while (*cmd == ' ' || *cmd == '\t')
 *              - check if the string is empty after trimming
 *              - trim trailing whitespace: end = cmd + strlen(cmd) - 1; while (end > cmd && (*end == ' ' || *end == '\t')) 
 *              - extract the first token(command) and store it
 *              - extract the second token(remove trailing whitespace of the second token): end2 = p + strlen(p) - 1; while (end2 > p && (*end2 == ' ' || *end2 == '\t'))
 *              - terminate array with NULL
 */
int parse_input(char *line, char *argv[])
{
	char *cmd = line;       /* create a pointer cmd pointing to the start of input line */
	char *end;
	char *p;
	char *end2;
	int count = 0;         /* initialize token count */

	while (*cmd == ' ' || *cmd == '\t')               /* skip the leading space or tabs */
		cmd++;

	if (*cmd == '\0')        /* cmd is a pointer to current char; *cmd is the value of current char at cmd */
		return (0);      /* if the string is empty after trimming, there is no token */
	
        /* strlen(cmd) calculates the length of string starting from cmd, excluding '\0'; at this point, cmd already skipped leading spaces, so it's trimmed string length */
	/* cmd + strlen(cmd) moves the pointer to the '\0' (at the end string) */
	/* cmd + strlen(cmd) - 1 points to the last char before '\0' */
	end = cmd + strlen(cmd) - 1;        

	/* end > cmd means we don't go past the beginning, if the character is a space or a tab, continue trimming， end moves backwards */
	while (end > cmd && (*end == ' ' || *end == '\t')) 
		*end-- = '\0';      /* replace spaces and tabs with '\0', then move end ptr left by one char */

	argv[0] = cmd;       /* first token is cmd(leading whitespace and trailing whitespace removed)*/
	count = 1;           /* tokne number is 1 */

	p = cmd;                                  /* assign p to start as the same position as cmd*/
	while (*p && *p != ' ' && *p != '\t')     /* move the pointer p forward, stop when it hits the first space, tab or '\0' */
		p++;                              /* move the pointer to the next char */

	if (*p)                                   /* if a delimiter was found, there is more input after the first token */
	{
		*p++ = '\0';                      /* replace the delimiter with '\0' to terminate the first token */

		while (*p == ' ' || *p == '\t')   /* skip spaces/tabs before second token */
			p++;
		if (*p)                           /* if the second token exists, store it and update the count */
		{
			argv[1] = p;
			count = 2;
			end2 = p + strlen(p) - 1;         /* trim trailing spaces and tabs from the second token */
			while (end2 > p && (*end2 == ' ' || *end2 == '\t'))
				*end2-- = '\0';
		}
	}
	argv[count] = NULL;     /* marks the end of the array */
	return (count);
}

