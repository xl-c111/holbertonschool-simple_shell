#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * main - super simple shell (runs full path commands, no args)
 * 
 * Return: Always 0
 * 
 * Description: 
 *
 *
 */
int main(void)
{
	 char *line;
	 size_t len;
	 ssize_t read;
	 pid_t child_pid;
	 int status;

	 while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}
		line[strcspn(line, "\n")] = '\0';

		child_pid = fork();
		if (child_pid < 0)
		{
			perror("fork failed");
			free(line);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			char *argv[] = {line, NULL};

			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}
	 free(line);
	 return (0);
}
