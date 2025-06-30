#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_path_dirs - prints each directory contained in the the environment
 *                   variable PATH, one directory per line.
 * Description: - getenv("PATH") to get the PATH variable
 *              - strdup() to make a copy so can be modified
 *              - strtok() to split the string by colon
 *              - printf() to print each directory
 *              - free(path_copy) to clean up allocated memory
 */
void print_path_dirs(void)
{
	char *path_env, *path_copy, *token;
	
	path_env = getenv("PATH");

	if (path_env == NULL)
	{
		perror("path");
		return;
	}
	path_copy = strdup(path_env);
	
	if (path_copy == NULL)
	{
		perror("strdup");
		return;		
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
	free(path_copy);
}

int main(void)
{
	print_path_dirs();
	return 0;
}

