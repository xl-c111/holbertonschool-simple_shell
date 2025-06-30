#include <stdio.h>
#include <string.h>

extern char** environ;

/**
 * _getenv - get the value of the environment variable
 * @name: a ptr to the given name of the environment variable to search for
 *
 * Return: ptr to the value string, NULL if not found
 *
 * Description: 
 * - strlen(name): get the length of the variable name
 * 
 * - int strncmp(const char *s1, const char *s2, size_t n);
 *   strncmp - compare up to n chars of s1 and s2
 *   @s1: the first string
 *   @s2: the second string
 *   @n: maximum number of chars to compare
 *   Return: 0 if first n chars equal;
 *           < 0 if s1 < s2;
 *           > 0 if s1 > s2
 *   strncmp(..., name, len): compare the begining of each string with name
 *
 * - environ[i][len]: char at the position len in the string environ[i]
 *   if "=" is at len position, that means a "key = value" form
 * 
 * - &environ[i][len + 1] return the ptr to the value of string
 *
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]); /* return the ptr to the value of string */
		}
		i++;
	}
	return (NULL);
}

int main(void)
{
	char *value = _getenv("PATH");
	
	if (value)
		printf("PATH = %s\n", value);
	else
		printf("PATH not found.\n");
	
	return (0);
}

