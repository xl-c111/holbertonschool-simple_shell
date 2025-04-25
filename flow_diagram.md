┌────────────────────────────┐
│       **int main(void)**       │
│  Start interactive shell loop │
└──────────────┬──────────────┘
               │
               ▼
┌──────────────────────────────┐
│     **void print_prompt()**      │
│ → print "$ " to stdout         │
└──────────────┬──────────────┘
               │
               ▼
┌────────────────────────────────────────────┐
│     getline(&line, &len, stdin)             │
│ → Read full user input line (e.g., "ls")     │
└──────────────┬─────────────────────────────┘
               │
               ▼
┌──────────────────────────────────────────────────────────┐
│     **int parse_line(char *line, char *argv[])**             │
│ → Split line into words                                     │
│ → Store command in argv[0], arguments in argv[1...]         │
└──────────────┬────────────────────────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│     **int handle_builtin(char *argv[], char *line, int last_status)**            │
│ → If "exit", call exit(last_status)                                             │
│ → If "env", print environment variables                                         │
│ → Return 1 if handled, else 0                                                   │
└───────┬───────────────────────────────────────────────────────────────────────┘
        │ (if not built-in)
        ▼
┌───────────────────────────────────────────────────────────────┐
│     **char *find_path(const char *command)**                      │
│ → If argv[0] contains '/', check if executable                  │
│ → Else get $PATH, split by ":"                                   │
│ → Iterate through directories                                   │
└───────┬───────────────────────────────────────────────────────┘
        ▼
┌──────────────────────────────────────────────────────────────────────────────────┐
│     **char *build_full_path(const char *dir, const char *command)**                  │
│ → Concatenate dir + "/" + command (e.g., "/usr/bin/ls")                             │
│ → Check access(fullpath, X_OK)                                                      │
│ → Return fullpath if executable; else free memory and try next                     │
└───────┬───────────────────────────────────────────────────────────────────────────┘
        │
        ▼
┌─────────────────────────────────────────────────────────────────────────────────────┐
│     **void fork_wait_execve(char *argv[], char *fullpath, int *raw_status)**             │
│ → fork a child process                                                              │
│ → In child: execve(fullpath, argv, environ)                                          │
│ → On fail: print error, exit(127)                                                    │
│ → In parent: waitpid(child_pid, &status, 0)                                          │
│ → Extract exit status using WIFEXITED and WEXITSTATUS                               │
└─────────────────────────────────────────────────────────────────────────────────────┘
        ▼
┌──────────────────────────────┐
│ Back to start (print prompt) │
└──────────────────────────────┘
