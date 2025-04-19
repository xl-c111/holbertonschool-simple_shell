#ifndef SHELL_H
#define SHELL_H

extern char **environ;

/* prompt.c */
void print_prompt(void);

/* execve.c */
void execute_command(char *const argv[]);

/* parse_line.c */
int parse_line(char *line, char *argv[]);

#endif
