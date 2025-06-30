#include <stdio.h>
/**
 * main - prints all the arguments
 * @ac: argument numbers
 * @av: argument vector
 *
 * Return: Always 0
 *
 */
int main(int ac, char **av)
{
	(void)ac;

	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}
