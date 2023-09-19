#include "main.h"

/**
 * get_node_ind - gets the index of a node
 * @head: pointer to list_t head-node
 * @list: pointer to node
 *
 * Return: index of node or -1
 */
ssize_t get_node_ind(list_t *head, list_t *list)
{
	size_t index = 0;

	while (head)
	{
		if (head == list)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}

