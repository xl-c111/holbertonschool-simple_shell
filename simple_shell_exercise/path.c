#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - search for executable files in the directories listed in PATH
 * @argc: number of command-line arguments
 * @argv: array of command-line arguments strings
 *
 * Return: 0 on success, 1 on error
 *
 * Description: 
 * 1, get the list of command names from the user
 *              for (i = 1; i < argc; i++)
 *
 * 2, retrieve and parse the PATH environment variable
 *              char *getenv(const char *name);
 *              - getenv() is a function used to get the value of an environment variable
 *              - @name: the name of variable you want to retrieve
 *
 * 3, Use strdup to safely tokenize the PATH
 *              char *strdup(const char *s);     ---->>> copy + allocate new memory
 *              - strdup duplicates a string by allocating new memory and copying the original content into it, because strtok modifies string
 *              - @s: the string to be copied
 *              - Return: a pointer to the newly duplicated string, NULL if fails
 *
 * 4, For each directory in PATH, build the full command path by combining a directory path(token) and a filename(argv[i])
 *              int snprintf(char *str, size_t size, const char *format, ...);
 *              - @str: the destination buffer 
 *              - @size: maximum number of bytes to write (including \0)
 *              - @format: format string (like printf)
 *              - ...values to fill into the format
 *
 * 4, Use access() to check if the file exists and is executable
 *              int access(const char *pathname, int mode);
 *              - check if the file pointed to by fullpath exists and is executable
 *              - @pathname: path of the file to check
 *              - mode: permission to check (read, write, execute, etc.)
 *                      - X_OK: check if executable
 *                      - R_OK: check if readable
 *                      - W_OK: check if writable
 *                      - F_OK: check if file exists
 */

int main(int argc, char *argv[])
{
	char *path_env, *path_copy, *token;    /* declare ptrs for environment path, a copy of path, a token for splitting */
	char fullpath[1024];     /* declare a buffer to hold the full path */
	int i;                   /* a loop index */
	
	if (argc < 2)            /* if argc is fewer than 2, it means there is no file passed */
	{
		fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
		return 1;
	}

	path_env = getenv("PATH");       /* path_env is a ptr to store the content of PATH, getenv() retrieves the value of PATH and store it in path_env */
	if (!path_env)                   /* if path not found */
	{
		perror("getenv PATH");
		return 1;
	}
	
	for (i = 1; i < argc; i++)              /* outer loop:loop through each user provided filename/command, skip argv[0] */
	{
		int found = 0;                  /* initialize a found flag to 0 (means not found) */
		path_copy = strdup(path_env);   /* allocate memory and copy the contents of string path_env into new allocation */
		
		if (!path_copy)                 /* if allocation fails */
		{
			perror("strdup");
			return 1;
		}
		
		token = strtok(path_copy, ":"); /* split the PATH string by colon : to get individual directory path */
		
		while (token != NULL)   /* inner loop: for each command, it loops through full PATH until it finds the executable file */        
		{
			/* build the full path to the file(argv[i]) by combining the directory name (token) */   
			/* %s/%s: the format string that tells snprintf to combine two strings with a slash / */
			snprintf(fullpath, sizeof(fullpath), "%s/%s", token, argv[i]);
			
			if (access(fullpath, X_OK) == 0)        /* check if the file exists and is executable */
			{
				printf("%s\n", fullpath);
				found = 1;                      /* set flag to 1(means found) and break the loop */
				break;
			}
			token = strtok(NULL, ":");              /* move to the next directory in PATH */
		}
		
		if (!found)
			printf("%s: not found\n", argv[i]);
		free(path_copy);
	}
	return 0;
}

