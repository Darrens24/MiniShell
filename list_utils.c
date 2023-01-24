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
