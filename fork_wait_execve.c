#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "shell.h"
/**
 * fork_wait_execve - forks a child process to execute external commands
 * @argv: array of strings representing command and its arguments
 * @command_path: full path to the command
 *
 * Return: in the child process, does not return if execve succeeds
 *         if execve fails, it prints an error and exits
 *         in the parent process, it wait for the child process to finish
 */

void fork_wait_execve(char *argv[], char *command_path)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		return;
	}

	if (pid == 0)
	{
		argv[0] = strdup(command_path);
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(command_path);
	}
}
