#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * main - entry point for the simple_shell program
 *
 * Return: EXIT_SUCCESS on normal shell exit
 *
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t bytes_read = 0;
	char *argv[2];
	pid_t pid;
	int status;

	while (1)
	{
		print_prompt();

		bytes_read = getline(&line, &len, stdin);
		if (bytes_read == -1)
			break;

		if (line[bytes_read - 1] == '\n')
			line[bytes_read - 1] = '\0';
		if (line[0] == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		if (pid == 0)
		{
			execute_command(argv);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	free(line);
	return (EXIT_SUCCESS);
}
