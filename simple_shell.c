#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * main - entry point for the simple_shell program
 * Return: - 0 if exited via the built-in 'exit' command without error
 *         - 1 if a command terminated abnormally
 *         - 127 if command was not found
 *         - or the exit status of the last executed command
 *
 * Description: 
 * 1, $? is a shell variable that holds the exit status of the last executed command
 *              - if the previous command executes successfully: $? is 0
 *              - if the command fails: $? is a non-zore value( like 2, 127)
 * 2, exit code - 0: command executed successfully                       
 *              - 1: general error / command execution failed (abnormal termination)
 *              - 2: misuse of shell builtin 
 *              - 126: command found but not executable
 *              - 127: command not found
 *
 * 2, getline automatically include '\n' at the end of input, replacing the newline char with NULL terminator is necessary       
 *              line[read_bytes - 1] = '\0';
 *
 * 3, argv is used to stored the parsed command and its arguments from user input
 *         so argv[0] is the actual command name(the first token parsed) like ls, echo, cat...
 *    argc is the number of parsed tokens( if (argc == 0) check if user just hit the ENTER button and doesn't input anything)
 */
int main(void)
{
	char *line = NULL;        /* user input line */
	char **argv[MAX_ARGS];    /* to store the parsed command and its arguments*/
	char *command_path;       /* the full path to the executable */
	size_t len = 0;           /* used for getline, current size of the line buffer */
	ssize_t bytes_read;       /* number of chars read by getline */
	int status = 0;           /* the exit status of current command*/
	int last_status = 0;      /* exit status of last command */
	int argc;                 /* number of command plus its arguments parsed by parse_line */
	int raw_status;           /* status return from waitpid */

	while (1)
	{
		print_prompt();

		bytes_read = getline(&line, &len, stdin);             /* read a line from standard input */
		if (bytes_read == -1)
			break;
		if (bytes_read > 0 && line[bytes_read - 1] == '\n')   
			line[bytes_read - 1] = '\0';                  /* replace the newline char with NULL terminator */

		argc = parse_line(line, argv);        /* parse_line: parse the input line into command and its arguments */
		if (argc == 0)                        /* if user just hit Enter without typing anything, argc will be 0 */
			continue;                     /* skips the rest current loop iteration and goes back to the top of loop */

		if (handle_builtin(argv, line, last_status))     /* check and execute built-in commands */
			continue;                        /* if a built-in command was executed, skip to next loop iteration */
		
		/* find the full path of command using the PATH variable */
		/* argv[0] is the first token parsed from user input, it's the actual command name (like ls, echo, cat)*/
		command_path = find_path(argv[0]);       
		if (command_path == NULL)                   /* if the command isn't found, set status to 127 and skip */    
		{
			status = 127;
			last_status = status;
			continue;
		}

		fork_wait_execve(argv, command_path, &raw_status);      /* forks and executes the command */
		free(command_path);   /* free the memory for allocated command path */
		
		if (WIFEXITED(raw_status))                     /* if child exits normally, extract the exit code */
			status = WEXITSTATUS(raw_status);
		else
			status = 1;     /* otherwise set status to 1(abnormal termination) */ 
		last_status = status;   /* update last_status to be used later (for $? or exit)*/
	}
	free(line);
	return (last_status);
}
