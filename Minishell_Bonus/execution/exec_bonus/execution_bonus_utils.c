/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:15:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/05 12:22:37 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_last_command(t_branch *map, t_branch *searched)
{
	while (map && map->dad)
		map = map->dad;
	if (map)
	{
		while (map && map->right)
		{
			if (is_and(map->cmd[0]) && map->err_code > 0)
				map = map->left;
			else if (is_or(map->cmd[0]) && map->err_code == 0)
				map = map->left;
			else
				map = map->right;
		}
	}
	if (map == searched)
		return (TRUE);
	return (FALSE);
}

int	is_last_pipe_command(t_branch *map)
{
	t_branch	*tmp;

	tmp = map;
	while (tmp && !is_pipe(tmp->cmd[0]))
		tmp = tmp->dad;
	if (tmp && tmp->dad && tmp->dad->cmd
		&& tmp->dad->cmd[0] && is_pipe(tmp->dad->cmd[0]))
		return (FALSE);
	if (tmp)
		while (tmp && tmp->right)
			tmp = tmp->right;
	if (tmp == map)
		return (TRUE);
	return (FALSE);
}

t_branch	*t_branchcpy(t_branch *map)
{
	t_branch	*tmp;

	tmp = malloc(sizeof(t_branch));
	tmp->subshell = map->subshell;
	tmp->dad = NULL;
	return (tmp);
}

int	check_valid_pipe(t_branch *map)
{
	t_branch	*tmp;

	tmp = map;
	while (tmp)
	{
		if (is_pipe(tmp->cmd[0]))
			return (1);
		tmp = tmp->dad;
	}
	return (0);
}
