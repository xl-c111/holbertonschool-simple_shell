#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_string - splits a string
 * @str: a pointer to string
 *
 * Return: a pointer to an array of strings (tokens)
 * Description: - char *strtok(char *str, const char *delim);
 *                       - breaks a string into a series of tokens using the characters in delim as delimiters
 *                       - return a pointer to the next token, or NULL if no more token found
 *              - store each token into array(tokens[i++] - token;)
 *              - realloc if the array is full (tokens = realloc(tokens, sizeof(char *) * bufsize);)
 *              - use a loop with strtok(NULL, ...) to get all tokens until NULL is returned
 *                       - strtok(str, delim): first call, pass the original string to tokenize
 *                       - strtok(NULL, delim): sebsuquent calls, continue tokenizing from where the last call left off 
 */
char **split_string(char *str)
{
	int i = 0;                   /* index for storing tokens */
	int bufsize = 64;            /* initial size of tokens array */
	char **tokens = malloc(sizeof(char *) * bufsize);  /* allocate memory for an array  of char *(each of which points to a token) */
	char *token;

	if (tokens == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	/* use strtok to extract the first token from str, using space, tab, carriage return, newline as delimiters */
	token = strtok(str, " \t\r\n");
	while (token != NULL)                /* loop as long as strtok returning valid tokens */
	{
		tokens[i++] = token;         /* store the current token in the array and increment the index */

		if (i >= bufsize)     /* if the array is full, increase the bufsize and reallocate memory */
		{
			bufsize += 64;
		        tokens = realloc(tokens, sizeof(char *) * bufsize);
		        if (tokens == NULL)
		        {
				perror("realloc failed");
				exit(EXIT_FAILURE);
		        }
		}
		token = strtok(NULL, " \t\r\n");     /* pass NULL tells continue from where you left off */
	}
	tokens[i] = NULL;     /* Null-terminate the array to indicate the end of tokens */
	return (tokens);
}
int main()
{
	char input[] = "hello world this is Holberton School";
	char **words = split_string(input);
	
	for (int i = 0; words[i] != NULL; i++) 
	{
		printf("word[%d]: %s\n", i, words[i]);
	}
	free(words);
	return 0;
}
