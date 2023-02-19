/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manip2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:42:18 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/19 16:43:06 by eleleux          ###   ########.fr       */
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
