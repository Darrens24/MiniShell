/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_final_boss.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:09:18 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/27 17:16:25 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_map_left(t_shell *shell, t_branch *map)
{
	if (map && is_and_or(map->cmd[0]))
		return (execution_bonus(shell, map->left));
	else if (map && is_operator(map->cmd[0]) && ++shell->nb_of_pipes)
		return (execution_bonus(shell, map->left));
	else
		return (EXIT_FAILURE);
}

int	execution_bonus(t_shell *shell, t_branch *map)
{
	t_branch	*tmp;

	if (map && map->left)
		execute_map_left(shell, map);
	else if (map && map->right)
	{
		if (map && is_pipe(map->cmd[0]) && ++shell->valid_pipe)
			shell->index_of_pipes++;
		if (map && is_and_or(map->cmd[0]))
		{
			if (is_and(map->cmd[0]) && map->err_code == 0)
				return (execution_bonus(shell, map->right));
			else if (is_or(map->cmd[0]) && map->err_code > 0)
				return (execution_bonus(shell, map->right));
			else if (map && is_pipe(map->cmd[0]))
				return (execution_bonus(shell, map->right));
			else
			{
				tmp = map;
				map = map->dad;
				if (map)
				{
					clean_node(tmp);
					return (execution_bonus(shell, map));
				}
				else if (!map)
				{
					clean_node(shell->tree->start);
					return (EXIT_SUCCESS);
				}
			}
		}
		else if (map && is_operator(map->cmd[0])
			&& shell->nb_of_pipes)
			return (execution_bonus(shell, map->right));
	}
	else if (map && !is_operator(map->cmd[0]))
	{
		tmp = map;
		map = map->dad;
		execute_command_clean_leaf(shell, tmp->cmd);
		if ((map && shell->nb_of_pipes != shell->index_of_pipes)
			|| (shell->last_index != -1 && shell->valid_pipe))
		{
			if (shell->last_index != -1 && shell->valid_pipe)
				close_fds(shell->fd[shell->index_of_pipes - 1]);
			if (shell->nb_of_pipes == shell->index_of_pipes)
			{
				shell->valid_pipe = 0;
				shell->last_index = -1;
			}
		}
		if (!is_pipe(map->cmd[0]))
		{
			wait_pid_mono(shell, shell->index_of_commands);
			shell->index_of_pid = shell->index_of_commands + 1;
		}
		if (shell->index_of_pipes == shell->nb_of_pipes && is_pipe(map->cmd[0]))
			wait_pids_bonus(shell->pid, shell,
				shell->index_of_commands, shell->index_of_pid);
		clean_node(tmp);
		map->err_code = g_err;
		shell->index_of_commands++;
		return (execution_bonus(shell, map));
	}
	else if (map && map->dad)
	{
		tmp = map;
		map = map->dad;
		map->err_code = tmp->err_code;
		clean_node(tmp);
		return (execution_bonus(shell, map));
	}
	return (EXIT_SUCCESS);
}
