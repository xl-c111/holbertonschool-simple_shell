#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64

extern char **environ;

void print_prompt(void);

char *_getenv(const char *name);

void fork_wait_execve(char *argv[], char *command_path, int *raw_status);

int parse_line(char *line, char *argv[]);

char *find_path(const char *command);

char *build_full_path(const char *dir, const char *command);

int handle_builtin(char *argv[]);

#endif
