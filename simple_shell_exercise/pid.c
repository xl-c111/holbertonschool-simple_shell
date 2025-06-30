#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0
 */
int main(void)
{
	pid_t my_pid, parent_of_my_pid;

	my_pid = getpid();
	parent_of_my_pid = getppid();

	printf("%d\n", my_pid);
	printf("%d\n", parent_of_my_pid);
	return (0);
}
