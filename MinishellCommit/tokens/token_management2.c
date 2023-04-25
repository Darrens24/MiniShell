/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:13:56 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/24 18:26:26 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjointok(char const *s1, char const *s2)
{
	char	*recipe;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	recipe = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!recipe)
		return (NULL);
	i = -1;
	while (s1[++i])
		recipe[i] = s1[i];
	j = 0;
	while (s2[j])
		recipe[i++] = s2[j++];
	recipe[i] = '\0';
	free((void *)s1);
	free((void *)s2);
	return (recipe);
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
		free(list->start->var);
		free(list->start);
		list->start = NULL;
		return (list);
	}
	temp = list->start;
	list->start = list->start->next;
	list->start->prev = NULL;
	temp->prev = NULL;
	temp->next = NULL;
	free(temp->var);
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
		free(list->end->var);
		free(list->end);
		list->end = NULL;
		return (list);
	}
	temp = list->end;
	list->end = list->end->prev;
	list->end->next = NULL;
	temp->prev = NULL;
	temp->next = NULL;
	free(temp->var);
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
