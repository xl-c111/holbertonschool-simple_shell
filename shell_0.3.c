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
 * Return: EXIT_SUCCESS on normal shell exit
 */
int main(void)
{
	char *line = NULL, *argv[MAX_ARGS], *command_path;
	size_t len = 0;
	ssize_t bytes_read;
	pid_t pid;
	int status, argc;

	while (1)
	{
		print_prompt();
		bytes_read = getline(&line, &len, stdin);
		if (bytes_read == -1)
			break;
		if (bytes_read > 0 && line[bytes_read - 1] == '\n')
			line[bytes_read - 1] = '\0';
		argc = parse_line(line, argv);
		if (argc == 0)
			continue;
		command_path = find_path(argv[0]);
		if (command_path == NULL)
		{
			status = 127;
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(command_path);
			continue;
		}
		if (pid == 0)
		{
			argv[0] = command_path;
			execute_command((char *const *)argv);
		}
		waitpid(pid, &status, 0);
		free(command_path);
	}
	free(line);
	return (EXIT_SUCCESS);
}
