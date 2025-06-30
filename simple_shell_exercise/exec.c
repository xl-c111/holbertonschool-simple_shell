#include <stdio.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 * Description: char *argv[] = {"/bin/ls", "-l", "/usr/", NULL}; 
 *              - define an array of strings that simulates the command-line argument passed to program, 
 *                it equals to run the shell command /bin/ls -l /usr/
 *              - in execve(argv[0], argv, NULL), this array is passed as argv
 */
int main(void)
{     
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL}; 
	
	printf("Before execve\n");
	
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error:");
	}
	printf("After execve\n");       /* this line only runs when execve fails */
	return (0);
}
