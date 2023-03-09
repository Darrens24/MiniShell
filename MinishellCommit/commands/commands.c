/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:16:31 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/08 17:47:29 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmdlst	*newp_back_cmd(t_cmdlst *cmdlst, char **command, int exec)
{
	t_cmd	*elem;
	int		i;

	elem = malloc(sizeof(*elem));
	if (!elem)
	{
		printf("Node: Dynamic allocation failed\n");
		return (NULL);
	}
	i = 0;
	while (command[i])
		i++;
	elem->var = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (command[++i])
		elem->var[i] = ft_strdup(command[i]);
	elem->var[i] = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	elem->exec = exec;
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
