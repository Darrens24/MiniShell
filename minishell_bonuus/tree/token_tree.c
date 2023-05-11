/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:49:50 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/10 08:50:15 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_toklst	*new_back_tok_wq(t_toklst *tokenlst, char *line, int quote)
{
	t_tok	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (NULL);
	elem->var = ft_strdup(line);
	elem->next = NULL;
	elem->prev = NULL;
	elem->quote = quote;
	elem->prio = 0;
	if (tokenlst->nb_elem == 0)
	{
		tokenlst->start = elem;
		tokenlst->end = elem;
	}
	else
	{
		tokenlst->end->next = elem;
		elem->prev = tokenlst->end;
		tokenlst->end = elem;
	}
	tokenlst->nb_elem++;
	return (tokenlst);
}

t_toklst	*new_front_tok_wq(t_toklst *tokenlst, char *line, int quote)
{
	t_tok	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (NULL);
	elem->var = ft_strdup(line);
	elem->next = NULL;
	elem->prev = NULL;
	elem->quote = quote;
	elem->prio = 0;
	if (tokenlst->nb_elem == 0)
	{
		tokenlst->start = elem;
		tokenlst->end = elem;
	}
	else
	{
		tokenlst->start->prev = elem;
		elem->next = tokenlst->start;
		tokenlst->start = elem;
	}
	tokenlst->nb_elem++;
	return (tokenlst);
}

t_toklst	*ft_tklstcpy(t_toklst *active_command)
{
	t_toklst	*new_list;
	t_tok		*temp;

	new_list = malloc(sizeof(t_toklst));
	if (!new_list)
		return (0);
	new_list->nb_elem = 0;
	temp = active_command->start;
	while (temp)
	{
		new_back_tok_wq(new_list, temp->var, temp->quote);
		new_list->end->prio = temp->prio;
		temp = temp->next;
	}
	return (new_list);
}
