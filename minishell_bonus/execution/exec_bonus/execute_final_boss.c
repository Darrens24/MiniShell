/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_final_boss.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:09:18 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/10 09:50:01 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int	execute_node_with_cmd(t_shell *shell, t_branch *map, t_branch *tmp)
{
	if (map)
	{
		if (is_and_or(tmp->cmd[0]))
			wait_pid_mono(shell, shell->index_of_commands - 1);
		else
			if (is_last_command(shell->tree->start, map))
				wait_pids_bonus(shell->pid, shell,
					shell->index_of_commands, shell->index_of_pid);
		map->err_code = g_err;
		clean(tmp->right, tmp);
		return (execution_bonus(shell, map));
	}
	else if (!map)
	{
		if (is_and_or(tmp->cmd[0]))
			wait_pid_mono(shell, shell->index_of_commands - 1);
		else
			if (is_last_command(shell->tree->start, tmp))
				wait_pids_bonus(shell->pid, shell,
					shell->index_of_commands, shell->index_of_pid);
		tmp->err_code = g_err;
		clean(shell->tree->start, tmp);
	}
	return (EXIT_SUCCESS);
}

void	norm_cleaning(t_branch *map)
{
	if (map && map->left)
		clean_node(map->left);
	else if (map && map->right)
		clean_node(map->right);
}

void	norm_waitpid(t_branch *tmp, t_shell *shell)
{
	if (is_last_pipe_command(tmp))
		wait_pids_bonus(shell->pid, shell,
			shell->index_of_commands, shell->index_of_pid);
}

void	free_subshell_data(t_branch *tmp, t_branch *map)
{
	clear_toklst(tmp->subshell);
	free(tmp->subshell);
	clear_toklst(tmp->left_command);
	free(tmp->left_command);
	clear_toklst(tmp->right_command);
	free(tmp->right_command);
	if (map)
		clean(tmp, map);
}

int	execution_bonus(t_shell *shell, t_branch *map)
{
	t_branch	*tmp;

	tmp = NULL;
	if (map && map->cmd_block > 0)
	{
		execute_map_subshell(map, tmp, shell);
	}
	else if (map && map->left)
		execute_map_left(shell, map);
	else if (map && map->right)
		execute_map_right(shell, map, tmp);
	else if (map && !is_operator(map->cmd[0]))
	{
		tmp = map;
		map = map->dad;
		execute_map_operator(shell, map, tmp);
	}
	else if (map && map->dad)
		execute_map_dad(shell, map, tmp);
	return (EXIT_SUCCESS);
}
