#include <unistd.h>
/**
 * print_prompt - outputs the shell prompt if in interactive mode
 */

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);
}
