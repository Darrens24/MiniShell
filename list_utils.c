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

t_chained	*list_copy(t_chained *list)
{
	t_chained	*new;
	t_node		*temp;

	new = malloc(sizeof(*new));
	if (!new)
		return (list);
	new->nb_elem = 0;
	temp = list->start;
	while (temp)
	{
		new = new_back_node(new, temp->variable);
		temp = temp->next;
	}
	return (new);

}

t_chained	*sort_list(t_chained *list)
{
	t_node		*temp;
	char		*buffer = NULL;
	t_chained	*new;

	new = list_copy(list);
	temp = new->start;
	while (temp->next)
	{
		if (ft_strncmp(temp->variable, temp->next->variable, (ft_strlen(temp->variable) + 1)) > 0)
		{
			buffer = ft_strdup(temp->variable);
			free(temp->variable);
			temp->variable = ft_strdup(temp->next->variable);
			free(temp->next->variable);
			temp->next->variable = ft_strdup(buffer);
			free(buffer);
			temp = new->start;
		}
		else
			temp = temp->next;
	}
	return (new);
}

void	print_list(char **list)
{
	int	i;

	i = 0;
	while (list && list[i])
	{
		ft_putstr_fd(list[i++], STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
	}
}
