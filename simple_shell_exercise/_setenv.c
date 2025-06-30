#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* to access and modify the environment, if the variable not found, we resize the array and add it */
extern char **environ;

/**
 * _setenv - changes or adds an environment variable (without using setenv)
 * @name: name of the environment variable
 * @value: value to set
 * @overwrite: tell the _setenv whether to replace the existing value of an environment
 *             variable if it already exists(you control the behavior by how you call the function)
 *             overwrite == 0, do not change the existing variable
 *             oevrwrite != 0, replace the existing variable
 *                 _setenv("PATH", "/my/custom/bin", 0); // does nothing
 *                 _setenv("PATH", "/my/custom/bin", 1); // updates PATH
 *             
 * return: 0 on success, -1 on failure
 * 
 *
 * Description: 
 * 1, validate the input, name and value must not be NULL, name must not contain '='
 *
 * 2, search existing environment array(environ[i])
 *    - loop through the env array
 *    - if found and overwrite == 0, do not modify and return
 *    - if overwrite != 0, build a new "name = value" string by sprintf(env_string, "%s=%s", name, value)
 *               - sprintf - write a format output string
 *               - @env_string: the destination buffer - where the formatted result will be stored
 *               - @"%s=%s": this is the format string(first string = second string) '%s' is palceholder for string, '=' is equal sign
 *               - @name: replace the first string
 *               - @value: replace the second string
 *
 * 3, if the variable not found
 *    - allocate a new, larger memory: new_environ = malloc((i + 2) * sizeof(char *));
 *    - copy the old environment entries into the new array by using a for loop: new_environ[j] = environ[j];
 *    - add the new "new = value" entry to the end: new_environ[i] = env_string; new_environ[i + 1] = NULL;
 *    - update environ to point to new array: environ = new_environ;
 * 
 *
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t name_len, value_len;
	char *env_string;
	char **new_environ;
	int i, j;

	/* strchr(name, '=') != NULL to check if there is a char '=' in the name string, if so, it's invalid */
	if (name == NULL || value == NULL || strchr(name, '=') != NULL)
		return (-1);

	name_len = strlen(name);
	value_len = strlen(value);
	
	/* loop through the env variable array */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* check whether the current nev string starts with name and is immediately followed by '=' */
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			if (overwrite == 0)      /* if the variable exists, do not modify it */
				return (0);
			
			env_string = malloc(name_len + value_len + 2);   /* allocate memory to store the string "name = value", 1 for '=', 1 for '\0' */
			if (env_string == NULL)           /* if allocation fails */
				return (-1);
			sprintf(env_string, "%s=%s", name, value);     /* construct the new environment string with format "name = value" and store it in env_string */
			
			environ[i] = env_string;           /* replace the pointer in environ[i] with new string */
			return (0);
		}
	}

	/* if not found, allocate memory for a new env array with i + 2 slots */
        /* i for existing variables, 1 for new env variable, 1 for '\0' */
	new_environ = malloc((i + 2) * sizeof(char *));
	
	if (new_environ == NULL)
		return (-1);

	for (j = 0; j < i; j++)    /* copy the existing i variable pointers from environ to new_environ*/
		new_environ[j] = environ[j];

	env_string = malloc(name_len + value_len + 2);     /* allocate memory for "name = value" string, 1 for '=', 1 for '\0' */
	if (env_string == NULL)
	{
		free(new_environ);
		return (-1);
	}

	sprintf(env_string, "%s=%s", name, value);        
	new_environ[i] = env_string;
	new_environ[i + 1] = NULL;
	environ = new_environ;
	
	return (0); 
}

void print_env(const char *name) {
    for (int i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=') {
            printf("[env] %s\n", environ[i]);
            return;
        }
    }
    printf("[env] %s not found\n", name);
}

int main(void) 
{
    printf("=== Testing _setenv ===\n");

    // 1. Set new variable
    printf("\n[TEST 1] Set NEWVAR=initial:\n");
    if (_setenv("NEWVAR", "initial", 0) == 0)
        print_env("NEWVAR");
    else
        printf("Failed to set NEWVAR\n");

    // 2. Try to overwrite it with overwrite=0 (should not change)
    printf("\n[TEST 2] Try to overwrite with overwrite=0:\n");
    if (_setenv("NEWVAR", "should_not_appear", 0) == 0)
        print_env("NEWVAR");

    // 3. Overwrite with overwrite=1
    printf("\n[TEST 3] Overwrite NEWVAR with 'updated':\n");
    if (_setenv("NEWVAR", "updated", 1) == 0)
        print_env("NEWVAR");

    // 4. Try to set illegal variable name
    printf("\n[TEST 4] Try invalid variable name (BAD=NAME):\n");
    if (_setenv("BAD=NAME", "value", 1) != 0)
        printf("Correctly rejected BAD=NAME\n");
    else
        printf("ERROR: BAD=NAME should not be accepted!\n");

    return 0;
}
