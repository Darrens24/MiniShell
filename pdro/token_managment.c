/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:26:07 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/28 13:50:39 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_emptytok(t_toklst *list)
{
        if (!list || list->nb_elem == 0)
                return (1);
        return (0);
}

t_toklst	*new_back_tok(t_toklst *tokenlst, char *line, int start, int end)
{
	t_tok	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (null);
	}
	elem->variable = ft_strdnup(line, start, end);
	elem->next = NULL;
	elem->prev = NULL;
	elem->quote = 0;
	if (list->nb_elem == 0)
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
	return (list);
}

t_toklst	*remove_back_tok(t_toklst *list)
{
	t_tok	*temp;

	if (is_emptytok(list))
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
