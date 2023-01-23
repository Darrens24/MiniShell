#include "minishell.h"

t_node	*go_to_end(t_chained *list)
{
	t_node	*temp;

	temp = list->start;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_chained	*new_front_node(t_chained *list, char *line)
{
	t_node	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (null_list());
	}
	elem->usr_cmd = ft_strdup(line);
	elem->next = NULL;
	elem->prev = NULL;
	if (list->nb_elem == 0)
	{
		list->start = elem;
		list->end = elem;
	}
	else
	{
		list->start->prev = elem;
		elem->next = list->start;
		list->start = elem;
		list->end = go_to_end(list);
	}
	list->nb_elem++;
	return (list);
}

t_chained	*new_back_node(t_chained *list, char *line)
{
	t_node	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (null_list());
	}
	elem->usr_cmd = line;
	elem->next = NULL;
	elem->prev = NULL;
	if (list->nb_elem == 0)
	{
		list->start = elem;
		list->end = elem;
	}
	else
	{
		list->end->next = elem;
		elem->prev = list->end;
		list->end = elem;
	}
	list->nb_elem++;
	return (list);
}

t_chained	*remove_front_node(t_chained *list)
{
	t_node	*temp;

	if (is_empty(list))
	{
		printf("ListRemove: Nothing to free\n");
		return (null_list());
	}
	if (list->nb_elem == 1)
	{
		list->nb_elem--;
		free(list->start);
		list->start = NULL;
		return (list);
	}
	temp = list->start;
	list->start = list->start->next;
	list->start->prev = NULL;
	temp->prev = NULL;
	temp->next = NULL;
	free(temp);
	temp = NULL;
	list->nb_elem--;
	return (list);
}

t_chained	*remove_back_node(t_chained *list)
{
	t_node	*temp;

	if (is_empty(list))
	{
		printf("ListRemove: Nothing to free\n");
		return (null_list());
	}
	if (list->nb_elem == 1)
	{
		list->nb_elem--;
		free(list->end);
		list->end = NULL;
		return (list);
	}
	temp = list->end;
	list->end = list->end->prev;
	list->end->next = NULL;
	temp->prev = NULL;
	temp->next = NULL;
	free(temp);
	temp = NULL;
	list->nb_elem--;
	return (list);
}
