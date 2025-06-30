#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints "$ ", wait for the user to enter a command
 *        prints it on the next line
 * 
 * Return: Always 0
 * Description: ssize_t getline(char **lineptr, size_t *n, FILE *stream)
 *             - @line： ptr to a string, when we pass to getline, we use &line(type of char**)
 *                       because getline wants to allocate and reallocate memory and change the value of line
 *             - @n: to store the allocated buffer size. If *line is NULL or not large enough, getline will use realloc to resize it
 *             - @stream: the standard input stream, getline reads from this stream, so it will wait user to type sth and hit enter
 */

int main (void)
{
	char *line = NULL;         /* declare a ptr to string, initialize it to NULL */
	size_t len = 0;            /* declare a variable len to store the allocated buffer size for getline */
	ssize_t read;              /* declare a signed size to store the number of chars read by getline  */

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);   /* &line == char**; &line == size_t * */

		if (read == -1)
		{
			printf("\n");
			break;
		}
		printf("%s", line);     /* getline() reads input including the new line, this will already include \n in the string */
	}
	free(line);
	return (0); 
}


