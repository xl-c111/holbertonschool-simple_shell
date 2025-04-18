#ifndef SHELL_H
#define SHELL_H

extern char **environ;

/* prompt.c */
void print_prompt(void);

/* execve.c */
void execute_command(char *const argv[]);

/* parse_input.c */
int parse_input(char *line, char *argv[]);

#endif
