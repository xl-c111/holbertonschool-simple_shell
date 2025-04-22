# C - Simple Shell
## Description
**hsh** is a simple UNIX command line interpreter written in C.  
It mimics the core behavior of `/bin/sh`, allowing users to execute commands in both interactive and non-interactive environments.
## Features
* **Displays** a shell prompt and executes user commands  
* **Parses and handles** command lines with or without arguments  
* **Supports non-interactive mode**, including piping and file redirection  
* **Implements built-in commands**:
  * `exit` – exits the shell
  * `env` – prints the current environment
* **Searches for and executes commands** using the `PATH` environment variable  
* **Handles errors properly** and supports EOF (e.g., `Ctrl+D`)
## Project Tasks
| Task           | Description                                                                 |
|----------------|-----------------------------------------------------------------------------|
|  Shell 0.1     | Display a prompt and execute basic one-word commands with no arguments.     |
|  Shell 0.2     | Extend to support commands with arguments.                                  |
|  Shell 0.3     | Search and execute commands using the `PATH`; skip `fork()` if not found.   |
|  Shell 0.4     | Add support for the built-in command `exit` (no arguments required).        |
|  Shell 1.0     | Add support for the built-in command `env` to print environment variables.  |
## Requirements
* Ubuntu 20.04 LTS
* C compiler: gcc -Wall -Werror -Wextra -pedantic -std=gnu89
* Follow Betty style guide
* No more than 5 functions per .c file
* All header files are include-guarded
* No unnecessary system calls
* Shell must not have memory leaks
## Allowed Functions and System Calls
Only standard C functions and a limited set of system calls are permitted, including:  
`fork`, `execve`, `wait`, `exit`, `read`, `write`, `getline`, `malloc`, `free`, `access`, `stat`, `opendir`, `readdir`, `signal`, `perror`, etc.
## Compilation
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
## Testing
### Run (interactive mode):
```
julien@ubuntu:/# ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
julien@ubuntu:/#
```
### Run (non-interactive mode):
```
julien@ubuntu:/# echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
julien@ubuntu:/# cat test_ls_2
/bin/ls
/bin/ls
julien@ubuntu:/# cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
julien@ubuntu:/#
```
## Exit Status
* Returns `0` if a command executes successfully
* Returns a non-zero value if an error occurs during command execution or built-in handling
## File Structure
| File                   | Description                                                                    |
|------------------------|--------------------------------------------------------------------------------|
| `simple_shell.c`       | Main shell loop: handles user input, built-in commands, and external execution |
| `print_prompt.c`       | Prints the shell prompt when in interactive mode                               |
| `fork_wait_execve.c`   | Forks and executes external commands using `execve()`                          |
| `parse_line.c`         | Tokenizes the input line into arguments                                        |
| `handle_builtin.c`     | Implements built-in commands: `exit` and `env`                                 |
| `find_path.c`          | Searches for a command in directories listed in the `PATH` environment variable|
| `shell.h`              | Header file containing function prototypes and macros                          |
| `README.md`            | Project overview and usage instructions                                        |
| `AUTHORS`              | List of project contributors                                                   |

## Authors
Xiaoling Cui, Faduma Abdihashi, Adam Pierzchalski 
