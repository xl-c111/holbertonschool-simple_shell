#ifndef SHELL_H
#define SHELL_H

/* prompt.c */
void print_prompt(void);

extern char **environ;

/* execve.c */
void execute_command(char *const argv[]);



#endif
