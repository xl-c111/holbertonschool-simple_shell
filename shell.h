#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64

extern char **environ;

void print_prompt(void);

char *_getenv(const char *name);

void execute_command(char *const argv[]);

int parse_line(char *line, char *argv[]);

char *find_path(const char *command);

#endif
