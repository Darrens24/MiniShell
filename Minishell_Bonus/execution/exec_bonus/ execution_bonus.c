/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    execution_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:55:45 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/25 15:09:26 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_command_clean_leaf(t_shell *shell, char **command)
{
	return (EXIT_SUCCESS);
}

int	execution_bonus(t_shell *shell, t_branch *map)
{
	t_branch	*tmp;

	if (map && map->left)
	{
		if (map && is_and_or(map->cmd[0]))
			return (execution_bonus(shell, map->left));
		else if (map && is_operator(map->cmd[0]) && ++shell->nb_of_pipes)
			return (execution_bonus(shell, map->left));
	}
	if (map && map->right)
	{
		if (map && is_and_or(map->cmd[0]))
		{
			if (is_and(map->cmd[0]) && map->err_code == 0)
				return (execution_bonus(shell, map->right));
			else if (is_or(map->cmd[0]) && map->err_code == 1)
				return (execution_bonus(shell, map->right));
			else
			{
				tmp = map;
				map = map->dad;
				clean(tmp);
				return (execution_bonus(shell, map->dad));
			}
		}
		else if (map && is_operator(map->cmd[0])
			&& shell->nb_of_pipes && ++shell->index_of_pipes)
			return (execution_bonus(shell, map->right));
	}
	if (map && !is_operator(map->cmd[0]))
	{
		tmp = map;
		map = map->dad;
		execute_command_clean_leaf(shell, tmp->cmd);
		return (execute_builtin_cmd(shell, map));
	}
	if (map && map->dad)
		return (execution_bonus(shell, map->dad));
	return (EXIT_SUCCESS);
}
