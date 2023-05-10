/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:27:43 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/10 09:49:25 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_map_operator(t_shell *shell, t_branch *map, t_branch *tmp)
{
	int	pipe;

	pipe = 0;
	if (map)
		pipe = is_pipe(map->cmd[0]);
	if (tmp && shell->out == TRUE && is_last_command(shell->tree->map, tmp))
		final_redirection(shell);
	execute_command_clean_leaf(shell, tmp->cmd, pipe);
	if (shell->index_of_pipes != shell->nb_of_pipes && shell->valid_pipe)
		close_fds(shell->fd[shell->index_of_pipes - 1]);
	else if (is_last_pipe_command(tmp))
	{
		close_fds(shell->fd[shell->index_of_pipes - 1]);
		shell->valid_pipe = 0;
		shell->last_index = -1;
	}
	if ((map && is_and_or(map->cmd[0])) || !map)
		wait_pid_mono(shell, shell->index_of_commands);
	else
		norm_waitpid(tmp, shell);
	if (map)
		map->err_code = g_err;
	norm_cleaning(map);
	shell->index_of_commands++;
	return (execution_bonus(shell, map));
}

int	execute_map_right(t_shell *shell, t_branch *map, t_branch *tmp)
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
			execute_node_with_cmd(shell, map, tmp);
		}
	}
	else if (map && is_operator(map->cmd[0])
		&& shell->nb_of_pipes)
		return (execution_bonus(shell, map->right));
	return (EXIT_FAILURE);
}

int	execute_map_left(t_shell *shell, t_branch *map)
{
	if (map && is_and_or(map->cmd[0]))
		return (execution_bonus(shell, map->left));
	else if (map && is_operator(map->cmd[0]) && ++shell->nb_of_pipes)
		return (execution_bonus(shell, map->left));
	else
		return (EXIT_FAILURE);
}

int	execute_map_dad(t_shell *shell, t_branch *map, t_branch *tmp)
{
	tmp = map;
	map = map->dad;
	map->err_code = tmp->err_code;
	if (tmp && map)
		clean(tmp, map);
	return (execution_bonus(shell, map));
}

int	execute_map_subshell(t_branch *map, t_branch *tmp, t_shell *shell)
{
	tmp = t_branchcpy(map);
	execute_subshell(shell, tmp);
	if (shell->index_of_pipes != shell->nb_of_pipes && shell->valid_pipe)
		close_fds(shell->fd[shell->index_of_pipes - 1]);
	else if (map && is_last_pipe_command(map))
	{
		close_fds(shell->fd[shell->index_of_pipes - 1]);
		shell->valid_pipe = 0;
		shell->last_index = -1;
	}
	free(tmp);
	tmp = map;
	map = map->dad;
	if ((map && is_and_or(map->cmd[0])) || !map)
		wait_pid_mono(shell, shell->index_of_commands);
	else
		norm_waitpid(tmp, shell);
	if (map)
		map->err_code = g_err;
	free_subshell_data(tmp, map);
	shell->index_of_commands++;
	execution_bonus(shell, map);
	return (EXIT_SUCCESS);
}
