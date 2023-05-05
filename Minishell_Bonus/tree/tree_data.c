/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:32:25 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/05 11:09:53 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_and_or(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0)
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0
		|| ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

int	and_or_in_cmd(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (is_and_or(temp->var) && temp->quote == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	operator_in_cmd(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (is_operator(temp->var) && temp->quote == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_toklst	*new_back_tok_wq(t_toklst *tokenlst, char *line, int quote)
{
	t_tok	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (NULL);
	}
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
	{
		printf("Node: Dynamic allocation failed\n");
		return (NULL);
	}
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
