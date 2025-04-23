#include <stdio.h>
#include <string.h>
#include "shell.h"
/**
 * _getenv - get the value of the environment variable
 * @name: a ptr to the given name of the environment variable to search for
 *
 * Return: ptr to the value string, NULL if not found
 * Description: - strncmp(environ[i], name, len) to compare the first len chars in environ[i] with name
 *              - environ[i][len] == '=' to check if the char after name is '=', which is the whole variable name 
 *              - return (&environ[i][len + 1]) returns the char after '=', which is the start of variable's value string
 *                If environ[i] is "PATH=/usr/bin", then environ[i][len + 1] is '/', pointing to "/usr/bin".
 */

char *_getenv(const char *name)
{
	int i = 0;
	int len = strlen(name);

	if (name == NULL)
		return (NULL);

	while (environ[i] != NULL)
	{
		/* strncmp to compare the first len chars of enbiron[i] with name and check if the next char after name is '='*/
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]);      /* return the ptr to the char after '=' in environ[i] */
		}
		i++;
	}
	return (NULL);
}

