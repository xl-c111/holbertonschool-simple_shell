#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 * Description: wait() makes the calling process (usually the parent) wait
 *              until one of its child processes terminates
 */
int main(void)
{
	pid_t child_pid;
	int status;
	
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		printf("Wait for me, wait for me\n");
		sleep(3);
	}
	else
	{
		wait(&status);  /* &status: a ptr to an int where the exit status of child will be stored */
		printf("Oh, it's all better now\n");
	}
	return (0);
}
