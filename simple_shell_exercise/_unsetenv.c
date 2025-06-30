#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * copy_environ - create a deep copy of the system environ
 * Return: a new NULL-terminated array of strings
 */
char **copy_environ(void)
{
	int count = 0;
	while (environ[count] != NULL)
		count++;
	
	char **new_environ = malloc((count + 1) * sizeof(char *));
	if (new_environ == NULL)
		return NULL;
	
	for (int i = 0; i < count; i++)
		new_environ[i] = strdup(environ[i]);
	
	new_environ[count] = NULL;
	return new_environ;
}

/**
 * _unsetenv -  deletes the variable name from the environment (without using unsetenv)
 * @name: the name of variable to delete
 *
 * Return: 0 on success, 1 on failure
 *
 * Description:
 * 1, validate input: name must not be NULL, name must not contain "="
 * 2, match full variable name only, followed by a "="
 * 3, shift remaining variables left, and reinsert NULL to maintain termination
 *    - by using a for loop: environ[j] = environ[j + 1];
 *    - reinsert NULL: environ[j] = NULL;
 *
 *
 */
int _unsetenv(const char *name)
{
	int i, j;
	size_t name_len;

	if (name == NULL || strchr(name, '=') != NULL)
		return (-1);

	name_len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			/* suppose the target variable is at the position i, starting from i */
			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];  /* replace the current position with the next one */
				/* loop continues until environ[j + 1] reaches NULL, meaning we copy the final NULL into environ[j] */
			}
			environ[j] = NULL;
			return (0);
		}
	}
	return (0);
}

int main(void)
{
	int i;
	
	printf("Before unset:\n");
	for (i = 0; environ[i] != NULL; i++)
		printf("  %s\n", environ[i]);
	
	if (_unsetenv("PATH") == 0)
		printf("\nPATH unset successfully.\n");
	else
		printf("\nFailed to unset PATH.\n");
	
	printf("\nAfter unset:\n");
	for (i = 0; environ[i] != NULL; i++)
		printf("  %s\n", environ[i]);
	
	return 0;
}

