#include <stdio.h>
#include <string.h>
#include "shell.h"
/**
 * _getenv - get the value of the environment variable
 * @name: a ptr to the given name of the environment variable to search for
 *
 * Return: ptr to the value string, NULL if not found
 */

char *_getenv(const char *name)
{
	int i = 0;
	int len = strlen(name);

	if (name == NULL)
		return (NULL);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

