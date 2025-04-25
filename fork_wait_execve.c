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
 * @command_path: full path to the executable command
 * @raw_status: a pointer to an int where the raw exit status of
 *              child process will be stored
 *
 * Return: in the child process, does not return if execve succeeds
 *         if execve fails, it prints an error and exits
 *         in the parent process, it wait for the child process to finish
 */

void fork_wait_execve(char *argv[], char *command_path, int *raw_status)
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execve(command_path, argv, environ);
		perror(command_path);
		exit(127);
	}
	else
	{
		waitpid(pid, raw_status, 0);
	}
}
