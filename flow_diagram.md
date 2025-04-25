```mermaid
flowchart TD
    A[int main(void)] --> B[void print_prompt()]
    B --> C[getline(&line, &len, stdin)]
    C --> D[int parse_line(char *line, char *argv[])]
    D --> E{handle_builtin?}
    E -- Yes --> F[handle exit() or env, then return]
    E -- No --> G[char *find_path(const char *command)]
    G --> H{command contains '/'?}
    H -- Yes --> I[Check access(argv[0], X_OK)]
    H -- No --> J[_getenv("PATH"), split by ':', iterate]
    J --> K[char *build_full_path(const char *dir, const char *command)]
    I --> L[fullpath returned to main]
    K --> L
    L --> M[void fork_wait_execve(argv[], fullpath, raw_status)]
    M --> N[child process: execve() or error 127]
    M --> O[parent process: waitpid, WIFEXITED, WEXITSTATUS]
    N --> P[Loop back to main]
    O --> P
```
