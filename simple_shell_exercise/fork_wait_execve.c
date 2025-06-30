#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main -  executes the command ls -l /tmp in 5 different child processes
 * 
 * Return: Always 0
 *
 * Description: The parent process creates 5 child processes sequentially.
 *              Each child process uses execve to run the command /bin/ls -l /tmp.
 *              The parent waits for each child to finish before creating the next one.
 *
 */
int main(void)
{
	pid_t child_pid;
	int i, status;

	for (i = 0; i < 5; i++)
	{
		child_pid = fork();

		if (child_pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};   /* child process: execute ls -l /tmp */

			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve failed");
				exit(EXIT_FAILURE);
			}

		}
		else
		{
			wait(&status);    /* parent process: wait for the child process to finish */
		}

	}
      	return (0);
}
