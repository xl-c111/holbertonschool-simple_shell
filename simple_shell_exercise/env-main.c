#include <stdio.h>

/**
 * main - prints the environment
 * @ac: argument count
 * @av: an array of arguments
 * @env: an array of environment variables, where each element is a 'key = value' string
 *       key = value string - key: name of the environment variable
 *                          - value: the content or value assigned to the key
 *                          - eg: "PATH = /usr/bin:/bin" is a "key = value" string 
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	unsigned int i;
	
	i = 0;
	
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
