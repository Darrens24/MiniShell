/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:57:16 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/27 09:11:20 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*remove_wildcard_tok(t_toklst *tokenlst)
{
	t_tok	*temp;

	temp = tokenlst->start;
	if (string_is_wildcard(temp->var))
	{
		remove_front_tok(tokenlst);
		return (temp);
	}
	while (temp && !string_is_wildcard(temp->var))
		temp = temp->next;
	remove_current_tok(temp, tokenlst);
	return (temp);
}

t_toklst	*new_wildcard_tok(t_toklst *tokenlst, char *buffer)
{
	t_tok	*elem;
	t_tok	*temp;

	temp = tokenlst->start;
	while (temp && !string_is_wildcard(temp->var))
		temp = temp->next;
	if (!temp->next)
		return (new_back_tok(tokenlst, buffer, 0,
			ft_strlen(buffer) + 1));
	elem = malloc(sizeof(*elem));
	if (!elem)
		return (tokenlst);
	elem->next = NULL;
	elem->prev = NULL;
	elem->quote = 1;
	elem->var = ft_strdup(buffer);
	temp->next->prev = elem;
	elem->next = temp->next;
	temp->next = elem;
	elem->prev = temp;
	tokenlst->nb_elem++;
	return (tokenlst);
}
