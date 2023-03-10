/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:57:38 by eleleux           #+#    #+#             */
/*   Updated: 2023/03/10 14:10:15 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_to_malloc(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

int	initialize_elem(t_cmd *elem, int exec, int i)
{
	elem->var[i] = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	elem->exec = exec;
	return (EXIT_SUCCESS);
}

t_cmdlst	*newp_back_cmd(t_cmdlst *cmdlst, char **command, int exec)
{
	t_cmd	*elem;
	int		i;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (NULL);
	elem->var = malloc(sizeof(char *) * (size_to_malloc(command) + 1));
	i = -1;
	while (command[++i])
		elem->var[i] = ft_strdup(command[i]);
	initialize_elem(elem, exec, i);
	if (cmdlst->nb_elem == 0)
	{
		cmdlst->start = elem;
		cmdlst->end = elem;
	}
	else
	{
		cmdlst->end->next = elem;
		elem->prev = cmdlst->end;
		cmdlst->end = elem;
	}
	cmdlst->nb_elem++;
	return (cmdlst);
}
