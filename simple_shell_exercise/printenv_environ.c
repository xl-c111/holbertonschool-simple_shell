#include <stdio.h>

extern char** environ;    /* declare a global variable environ, which stores all environment variables as an array of "key = value" strings */

/**
 * main - prints all environment variables using 'environ'
 *
 * Return: Always 0
 *
 *
 */
int main(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
