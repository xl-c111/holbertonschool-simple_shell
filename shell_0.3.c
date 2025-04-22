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
 * Return: - 127 if command was not found
 *         - 0 if exited via the built-in 'exit' command without error
 *         - or the exit status of the last executed command
 */
int main(void)
{
	char *line = NULL, *argv[MAX_ARGS], *command_path;
	size_t len = 0;
	ssize_t bytes_read;
	int status, argc, raw_status;

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

		if (handle_builtin(argv))
		{
			exit(status);
		}

		command_path = find_path(argv[0]);
		if (command_path == NULL)
		{
			status = 127;
			continue;
		}
		fork_wait_execve(argv, command_path, &raw_status);
		if (WIFEXITED(raw_status))
			status = WEXITSTATUS(raw_status);
		else
			status = 1;
	}
	free(line);

	return (status);
}
