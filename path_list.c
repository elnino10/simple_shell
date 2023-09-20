#include "main.h"

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to lists
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *temp;
	const char *s = str;

	if (!head)
		return (NULL);
	temp = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (s)
	{
		new_node->dir = _strdup(s);
		if (!new_node->dir)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * del_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_node_at_index(list_t **head, unsigned int index)
{
	list_t *temp, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->dir);
		free(temp);
		return (1);
	}
	temp = *head;
	while (temp)
	{
		if (i == index)
		{
			prev_node->next = temp->next;
			free(temp->dir);
			free(temp);
			return (1);
		}
		i++;
		prev_node = temp;
		temp = temp->next;
	}
	return (0);
}

/**
 * node_prefix - returns node that starts with prefix
 * @list: pointer to head-node
 * @prefix: string to match
 * @ch: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *node_prefix(list_t *list, char *prefix, char ch)
{
	char *a = NULL;

	while (list)
	{
		a = start_str(list->dir, prefix);
		if (a && ((ch == -1) || (*a == ch)))
			return (list);
		list = list->next;
	}

	return (NULL);
}

/**
 * list_strings - returns array of strings of list->dir
 * @head: pointer to head-node
 *
 * Return: array of strings
 */
char **list_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->dir) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->dir);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * list_length - gets length of linked list
 * @head: pointer to head-node
 *
 * Return: size of list
 */
size_t list_length(const list_t *head)
{
	size_t num = 0;

	while (head)
	{
		head = head->next;
		num++;
	}
	return (num);
}

