#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "shell.h"
/**
 * fork_wait_execve - forks a child process to execute external commands
 * @argv: list of arguments( including command and its arguments)
 *        - it is passesd to execve as the second argument, telling system how to execute it
 *        - argv[0] is the program name, which equals to basename(command_path), argv[i] are program arguments
 * @command_path: full path to the executable command
*         - it is passed to execve as the first argument, telling system actual location of executable)
 * @raw_status: a pointer to int where the raw exit status of child process will be stored 
 *
 * Return: in the child process, does not return if execve succeeds
 *         if execve fails, it prints an error and exits
 *         in the parent process, it wait for the child process to finish
 * 
 * Description: 1，execve(command_path, argv, environ)
 *              - repplace the current(child) process with a new program(which is located in command_path)
 *              - so the child process tansforms into a new program you want to run(like ls, gcc)
 *              - the parent remains unchnaged until child process terminates
 *              2， int waitpid(pid_t pid, int *status, int options);
 *              - @pid: the process ID of child process
 *              - @status: a ptr to an int where the exit status of child process will be stored, 
 *                         it's a raw status, must be interpreted using macros like WIFEXITED() or WEXITSTATUS() to get the real exit code
 *                         - WIFEXITED(status) to check if the child exits normally
 *                         - WEXITSTATUS(status) to extract the exit code from raw status
 *              - @options: 0 means "default behavior" — just wait for the child to terminate
 */

void fork_wait_execve(char *argv[], char *command_path, int *raw_status)
{
	pid_t pid;

	pid = fork();          /* create a new process */

	if (pid == -1)         /* check if fork failed */
	{
		perror("fork");
		return;
	}

	if (pid == 0)          /* if in the child process */
	{
		/* replace the child process with a new program located in command_path */
		/* if execve succeeds, the current process is replaced, non of following lines run */
		execve(command_path, argv, environ);  
		perror(command_path);       /* this line only runs when execve fails*/
		exit(127);                  /* 127 means command not found */
	}
	else                                /* this block is executed in parent process */
	{
		waitpid(pid, raw_status, 0);  /* wait for the child process to terminate, store its status in raw_status*/
	}
}
