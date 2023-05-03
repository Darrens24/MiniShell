/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manip2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:42:18 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/03 15:40:28 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*remove_current_node(t_node *node, t_chained *lst)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	if (!node->prev)
	{
		remove_front_node(lst);
		return (node);
	}
	if (!node->next)
	{
		remove_back_node(lst);
		return (node);
	}
	free(node->variable);
	lst->nb_elem--;
	node->variable = NULL;
	node->prev = NULL;
	node->next = NULL;
	free(node);
	node = NULL;
	return (node);
}

t_chained	*new_current_node(t_chained *lst, int index, char *variable)
{
	t_node	*elem;
	t_node	*temp;

	temp = lst->start;
	while (temp && --index > 0)
		temp = temp->next;
	if (!temp->prev)
		return (new_front_node(lst, variable));
	else if (!temp->next)
		return (new_back_node(lst, variable));
	else
	{
		elem = malloc(sizeof(*elem));
		if (!elem)
			return (lst);
		elem->variable = ft_strdup(variable);
		elem->next = NULL;
		elem->prev = NULL;
		temp->next->prev = elem;
		elem->next = temp->next;
		temp->next = elem;
		elem->prev = temp;
		lst->nb_elem++;
	}
	return (lst);
}
