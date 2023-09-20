#include "main.h"

/**
 **_memset - fills memory with a constant byte
 *@m: pointer to memory area
 *@b: byte to fill with *m
 *@n: number of bytes to be filled
 *
 *Return: pointer to the memory area m
 */
char *_memset(char *m, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		m[i] = b;
	return (m);
}

/**
 * free_grid - frees a 2 dimensional grid previously created
 * @grid: double pointer to grid
 *
 * Return: nothing
 */
void free_grid(char **grid)
{
	char **new_grid = grid;

	if (!new_grid)
	{
		return;
	}

	while (*grid)
		free(*grid++);
	free(new_grid);
}

/**
 * free_list_t - frees nodes of a list
 * @head_ptr: pointer to head-node pointer
 *
 * Return: nothing
 */
void free_list_t(list_t **head_ptr)
{
	list_t *list, *next_node, *head_node;

	if (!head_ptr || !*head_ptr)
		return;

	head_node = *head_ptr;
	list = head_node;
	while (list)
	{
		next_node = list->next;
		free(list->dir);
		free(list);
		list = next_node;
	}

	*head_ptr = NULL;
}

/**
 * free_ptr - frees pointer
 * @ptr: pointer of the pointer to free
 *
 * Return: 1 if free or 0 otherwise
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}

/**
 * __realloc - reallocates memory block
 * @ptr: pointer to previously allocated block
 * @prev_size: byte size of previous block
 * @curr_size: byte size of new block
 *
 * Return: pointer to allocated memory block
 */
void *__realloc(void *ptr, unsigned int prev_size, unsigned int curr_size)
{
	char *new;

	if (!ptr)
		return (malloc(curr_size));

	if (!curr_size)
		return (free(ptr), NULL);

	if (curr_size == prev_size)
		return (ptr);

	new = malloc(curr_size);
	if (!new)
		return (NULL);

	prev_size = prev_size < curr_size ? prev_size : curr_size;
	while (prev_size--)
		new[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);

	return (new);
}

