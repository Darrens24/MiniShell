#include "minishell.h"

t_chained	*null_list(void)
{
	return (NULL);
}

int	is_empty(t_chained *list)
{
	if (!list || list->nb_elem == 0)
		return (1);
	return (0);
}

t_chained	*sort_list(t_chained *list)
{
	t_chained	*temp;
	char		*buffer;

	temp = list;
	while (list->start->next)
	{
		if (ft_strncmp(list->start->variable, list->start->next->variable, (ft_strlen(list->start->variable) + 1)) >= 0)
		{
			buffer = ft_strdup(list->start->variable);
			//free(temp->variable);
			list->start->variable = ft_strdup(list->start->next->variable);
			//free(temp->next->variable);
			list->start->next->variable = ft_strdup(buffer);
			free(buffer);
			list = temp;
		}
		else
			list->start = list->start->next;
	}
	return (list);
}

void	print_list(t_chained *list)
{
	t_node *temp;

	temp = list->start;
	while (temp)
	{
		printf("%s\n", temp->variable);
		temp = temp->next;
	}
}
