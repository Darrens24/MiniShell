/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:26:07 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/14 10:37:40 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_emptytok(t_toklst *list)
{
	if (list->nb_elem == 0)
		return (1);
	return (0);
}

void	print_toklst(t_toklst *list)
{
	t_tok	*temp;

	temp = list->start;
	while (temp)
	{
		printf("%s\n", temp->var);
		temp = temp->next;
	}
}

t_tok	*remove_current_tok(t_tok *tok, t_toklst *list)
{
	if (tok->prev && tok->next)
	{
		tok->prev->next = tok->next;
		tok->next->prev = tok->prev;
	}
	if (!tok->prev)
	{
		remove_front_tok(list);
		return (tok);
	}
	if (!tok->next)
	{
		remove_back_tok(list);
		return (tok);
	}
	free(tok->var);
	list->nb_elem--;
	tok->var = NULL;
	tok->prev = NULL;
	tok->next = NULL;
	free(tok);
	tok = NULL;
	return (tok);
}

t_toklst	*new_back_tok(t_toklst *tokenlst, char *line, int start, int end)
{
	t_tok	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (NULL);
	}
	elem->var = ft_strndup(line, start, end);
	elem->next = NULL;
	elem->prev = NULL;
	elem->quote = 0;
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

t_toklst	*new_back_tok_quote(t_toklst *tokenlst, char *line, int start, int end)
{
	t_tok	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (NULL);
	}
	elem->var = ft_strndup(line, start, end);
	elem->next = NULL;
	elem->prev = NULL;
	elem->quote = 1;
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

t_toklst	*remove_front_tok(t_toklst *list)
{
	t_tok	*temp;

	if (is_emptytok(list))
	{
		printf("ListRemove: Nothing to free\n");
		return (list);
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

t_toklst	*remove_back_tok(t_toklst *list)
{
	t_tok	*temp;

	if (is_emptytok(list))
	{
		printf("ListRemove: Nothing to free\n");
		return (NULL);
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

void	clear_toklst(t_toklst *lst)
{
	while (lst->nb_elem)
		remove_back_tok(lst);
}

void	clear_chained_lst(t_chained *lst)
{
	while (lst->nb_elem)
		remove_back_node(lst);
}
