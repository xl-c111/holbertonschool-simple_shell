```mermaid
flowchart TD
    A[main()] --> B[print_prompt() <br> print "$ "]
    B --> C[getline(&line, &len, stdin) <br> read user input]
    C --> D[parse_line(line, argv[]) <br> split into command + args]
    D --> E[handle_builtin(argv) <br> if 'exit', call exit() <br> if 'env', print env]
    E -->|not built-in| F[find_path(argv[0])]
    F --> G{command contains '/'}
    G -->|Yes| H[check access(argv[0], X_OK) <br> if exec, return argv[0]]
    G -->|No| I[getenv("PATH") <br> split by ":"]
    I --> J[build_full_path(dir, command) <br> e.g., "/bin/ls"]
    J --> K{access(fullpath, X_OK)?}
    K -->|Yes| L[return fullpath]
    K -->|No| M[try next dir in PATH]
    L --> N[fork_wait_execve(argv, fullpath) <br> fork + execve()]
    M --> J
```
