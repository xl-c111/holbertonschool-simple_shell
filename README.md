# C - Simple Shell
## Description
This project is a basic UNIX command line interpreter, a simplified shell implementation written in C. It mimics the core behavior of `/bin/sh`, allowing users to execute commands in both interactive and non-interactive environments.
## Features
* Display prompt and execute commands
* Handle command lines with or without arguments
* Handle non-interactive mode via piping or redirection
* Support for built-ins:
    * `exit`
    * `env`
* Search and execute commands using the `PATH`
* Proper error handling and EOF (`Ctrl+D`) support
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
## File Structure
| File                 | Description                               |
|----------------------|-------------------------------------------|
| `shell.c`            | Main shell loop, handles input + dispatch |
| `print_prompt.c`     | Handles printing the shell prompt         |
| `execute_command.c`  | Forks and executes external commands      |
| `parse_line.c`       | Tokenizes input line into arguments       |
| `shell.h`            | Header file containing prototypes & macros|
| `README.md`          | Project documentation                     |
| `AUTHORS`            | A full list of contributors               |
## Authors
Xiaoling Cui, Faduma Abdihashi, Adam Pierzchalski 
