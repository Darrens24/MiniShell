/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:22 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/22 14:09:43 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char		*buffer;
	t_chained	*new;

	new = list_copy(list);
	temp = new->start;
	while (temp->next)
	{
		if (ft_strncmp(temp->variable, temp->next->variable,
				(ft_strlen(temp->variable) + 1)) > 0)
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

void	print_list(t_chained *list)
{
	t_node	*temp;

	temp = list->start;
	while (temp)
	{
		printf("%s\n", temp->variable);
		temp = temp->next;
	}
}
