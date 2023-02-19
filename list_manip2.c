/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manip2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:42:18 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/19 21:19:08 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*remove_current_node(t_node *node, t_chained *lst)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
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

t_chained	*new_current_node(chained *lst, int index, char *variable)
{
	t_node	*elem;
	t_node	*temp;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (lst);
	}
	elem->variable = ft_strdup(variable);
	elem->next = NULL;
	elem->prev = NULL;
	elem->quote = 0;
	temp = lst->start;
	while (temp && index--)
		temp = temp->next;
	if (!temp->next)
		new_back_node(lst);
	else
	{
		temp->next->prev = elem;
		elem->next = temp->next;
		temp->next = elem;
		elem->prev = temp;
	//	tokenlst->end->next = elem;
	//	elem->prev = tokenlst->end;
	//	tokenlst->end = elem;
		lst->nb_elem++;
	}
	return (lst);
}
