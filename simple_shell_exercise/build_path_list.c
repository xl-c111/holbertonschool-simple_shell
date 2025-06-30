#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
/**
 * struct path_node - Node in a linked list of directories
 * @dir: holds a directory string
 * @next: pointer to the next code
 */
typedef struct path_node
{
	char *dir;
	struct path_node *next;
}path_node;

/**
 * build_path_list - builds a linked list of directories in the PATH variable
 *
 * Return: pointer to the head of the linked list, or NULL on failure
 *
 * Description:
 * - getenv to get the value of PATH
 * - strdup to make a modifiable copy for strtok
 * - strtok to split the copied PATH into individual directories
 * - malloc to allocate memory for each node
 * - new_node->dir = strdup(token) to copy the current string into new_node
 * - link each directory by using head and current pointer
 *   - head always points the head of the lost, once it set, it will never move; 
 *   - current always points the last node currently in the list
 *
 */
path_node *build_path_list(void)
{
	char *path_env, *path_copy, *token;
	/* head points the head of the lkinked list, current points the last node of the list*/
	path_node *head = NULL, *current = NULL, *new_node;    

	path_env = getenv("PATH");               /* if PATH not found */
	if (path_env == NULL)
	{
		perror("getenv");
		return (NULL);
	}
	path_copy = strdup(path_env);            /* make a modifiable copy */

	if (path_copy == NULL)                   /* if memory allocation fails */
	{
		perror("strdup");
		return (NULL);
	}
	token = strtok(path_copy, ":");          /* split the copied PATH by delimiter colon */
	while (token != NULL)
	{
		new_node = malloc(sizeof(path_node));
		if (new_node == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}

		new_node->dir = strdup(token);      /* copy the directory string into the new_node */
		new_node->next = NULL;              /* initialize the next ptr to NULL */

		if (head == NULL)
		{
			head = new_node;            /* if it's the first node, assign it as head */
			current = head;
		}
		else
		{
			current->next = new_node;   /* if not, link the new_node after current and moves the pointer */
			current = new_node;
		}
		token = strtok(NULL, ":");          /* get the next directory in PATH */
	}
	free(path_copy);
	return (head);
}
/**
 * free_path_list - free the memory used by a linked list of PATH dorectory 
 * @head: ptr to the head of the linked list
 *
 */
void free_path_list(path_node *head)
{
	path_node *temp;                  /* a temporary ptr to hold the current node */
	
	while (head != NULL)              /* while there are nodes left in the list */
	{
		temp = head;              /* save the current node to temp so it can be freed later */
		head = head->next;        /* then move the head to next node to prepare to the next iteration */
		free(temp->dir);          /* free the string stored in temp */
		free(temp);               /* free the current node it self */
	}
}

int main(void)
{
	path_node *head = build_path_list();
	path_node *curr = head;
	
	while (curr)
	{
		printf("%s\n", curr->dir);
		curr = curr->next;
	}
	
	free_path_list(head);
	return 0;
}

