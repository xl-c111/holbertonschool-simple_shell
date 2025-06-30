#include <stdio.h>

extern char **environ;

/**
 * main - compares env and environ addresses
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 * @env: environment array passed to main
 *
 * Return: Always 0
 *
 * Description: - they will return the same address
 *              - env is passed in as a parameter to main, while environ is a global viriable provided by the system. 
 *              - they are just two different ways to access the same array
 */
int main(int ac, char **av, char **env)
{
	printf("Address of env     : %p\n", (void *)env);
	printf("Address of environ : %p\n", (void *)environ);
	
	return 0;
}

