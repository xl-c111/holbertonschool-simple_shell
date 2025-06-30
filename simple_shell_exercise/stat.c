#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - use stat to check whether each given file path exists
 * @ac: the number of arguments
 * @av: an array of strings(char pointers), one for each argument
 *      (av[0] is always the program name, command line arguments start from av[1])
 * Return: Always 0, 1 if no file path provided
 * 
 * Description: - input validation if (ac < 2);
 *              - argument iteration while (av[i]); i++(i set to 1 to skip the program name);
 *              - file existence checking using stat()
 *                       int stat(const char *pathname, struct stat *statbuf){
 *                           off_t     st_size;
 *                           mode_t    st_mode;
 *                           nlink_t   st_nlink;
 *                       };
 *                       - @pathname: path of the file you want to inspect
 *                       - @statbuf: a pointer to a struct stat to store file info
 * 
 *
 *
 */
int main(int ac, char **av)
{
	unsigned int i;       /* used to iterate through command-line arguments, start from av[1] */
	struct stat st;       /* a variable st of type struct stat to store the file information */
	
	if (ac < 2)           /* check if the argument number is fewer than 2, means there is only av[0] = program name */
	{
		printf("Usage: %s path_to_file ...\n", av[0]);
		return (1);
	}
	
	i = 1;                 /* set i to 1 to skip the program name and start checking from the first file path */
	while (av[i])
	{
		printf("%s:", av[i]);               /* prints the file path being checked */
		
		if (stat(av[i], &st) == 0)          /* call stat() to get the file information, returns 0 if success */
		{
			printf(" FOUND\n");
		}
		else
		{
			printf(" NOT FOUND\n");
		}
		i++;
	}
	return (0);
}
