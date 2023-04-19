/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:57:38 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/19 09:35:18 by pfaria-d         ###   ########.fr       */
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

	elem = malloc(sizeof(t_cmd));
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

t_cmdlst	*remove_back_cmd(t_cmdlst *cmdlst)
{
	t_cmd	*temp;

	if (cmdlst->nb_elem == 0)
		return (NULL);
	if (cmdlst->nb_elem == 1)
	{
		cmdlst->nb_elem--;
		free_array(cmdlst->end->var);
		free(cmdlst->end);
		cmdlst->end = NULL;
		return (cmdlst);
	}
	temp = cmdlst->end;
	cmdlst->end = cmdlst->end->prev;
	cmdlst->end->next = NULL;
	temp->prev = NULL;
	temp->next = NULL;
	free_array(temp->var);
	free(temp);
	temp = NULL;
	cmdlst->nb_elem--;
	return (cmdlst);
}

void	clear_cmd_lst(t_cmdlst *cmdlst)
{
	while (cmdlst->nb_elem)
		remove_back_cmd(cmdlst);
	//free(cmdlst);
}
