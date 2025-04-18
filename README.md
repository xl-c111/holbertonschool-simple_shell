# C - Simple Shell
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
## Requirements
## Allowed Functions and System Calls
## Compilation
<pre><code>bash gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh </code></pre>
## Testing
### Run (interactive mode):
<pre><code>text julien@ubuntu:/# ./hsh 
           ($) /bin/ls 
           hsh main.c shell.c 
           ($) 
           ($) exit julien@ubuntu:/# </code></pre>
### Run (non-interactive mode):
<pre><code>console julien@ubuntu:/# echo "/bin/ls" | ./hsh
                   hsh main.c shell.c test_ls_2 
                   julien@ubuntu:/# cat test_ls_2 
                   /bin/ls 
                   /bin/ls 
                   julien@ubuntu:/# cat test_ls_2 | ./hsh 
                   hsh main.c shell.c test_ls_2 
                   hsh main.c shell.c test_ls_2 
                   julien@ubuntu:/# </code></pre>
## Project Tasks
| Task           | Description                                                                 |
|----------------|-----------------------------------------------------------------------------|
|  Shell 0.1     | Display a prompt and execute basic one-word commands with no arguments.     |
|  Shell 0.2     | Extend to support commands with arguments.                                  |
|  Shell 0.3     | Search and execute commands using the `PATH`; skip `fork()` if not found.   |
|  Shell 0.4     | Add support for the built-in command `exit` (no arguments required).        |
|  Shell 1.0     | Add support for the built-in command `env` to print environment variables.  |

## Testing


## Authors
