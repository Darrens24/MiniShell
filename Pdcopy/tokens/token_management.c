/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:26:07 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/01 10:40:31 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_toklst	*new_front_tok(t_toklst *list, char *line)
{
	t_tok	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (0);
	elem->var = ft_strdup(line);
	elem->next = NULL;
	elem->prev = NULL;
	elem->prio = 0;
	if (list->nb_elem == 0)
	{
		list->start = elem;
		list->end = elem;
	}
	else
	{
		list->start->prev = elem;
		elem->next = list->start;
		list->start = elem;
		//list->end = go_to_end_tok(list);
	}
	list->nb_elem++;
	return (list);
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

t_toklst	*new_back_tok_q(t_toklst *tokenlst, char *line, int start, int end)
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
