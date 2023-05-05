/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_final_boss.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:09:18 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/04 15:16:30 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int	is_last_command(t_branch *map, t_branch *searched)
{
	while (map && map->dad)
		map = map->dad;
	if (map)
		while (map && map->right)
		{
			if (is_and(map->cmd[0]) && map->err_code > 0)
				map = map->left;
			else if (is_or(map->cmd[0]) && map->err_code == 0)
				map = map->left;
			else
				map = map->right;
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
	if (tmp)
		while (tmp && tmp->right)
			tmp = tmp->right;
	if (tmp == map)
		return (TRUE);
	return (FALSE);
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
			if (map)
			{
				if (is_and_or(tmp->cmd[0]))
					wait_pid_mono(shell, shell->index_of_commands - 1);
				else
				{
					if (is_last_command(shell->tree->start, map))
						wait_pids_bonus(shell->pid, shell,
							shell->index_of_commands, shell->index_of_pid);
				}
				map->err_code = g_err;
				clean(tmp->right, tmp);
				return (execution_bonus(shell, map));
			}
			else if (!map)
			{
				if (is_and_or(tmp->cmd[0]))
					wait_pid_mono(shell, shell->index_of_commands - 1);
				else
				{
					if (is_last_command(shell->tree->start, tmp))
						wait_pids_bonus(shell->pid, shell,
							shell->index_of_commands, shell->index_of_pid);
				}
				tmp->err_code = g_err;
				clean(shell->tree->start, tmp);
				return (EXIT_SUCCESS);
			}
		}
	}
	else if (map && is_operator(map->cmd[0])
		&& shell->nb_of_pipes)
		return (execution_bonus(shell, map->right));
	return (EXIT_FAILURE);
}


int	execute_map_dad(t_shell *shell, t_branch *map, t_branch *tmp)
{
	tmp = map;
	map = map->dad;
	map->err_code = tmp->err_code;
	clean_node(tmp);
	return (execution_bonus(shell, map));
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

int	execute_map_operator(t_shell *shell, t_branch *map, t_branch *tmp)
{
	execute_command_clean_leaf(shell, tmp->cmd);
	if (shell->index_of_pipes != shell->nb_of_pipes && shell->valid_pipe)
	{
		/* fprintf(stderr, "je close fd[%d]\n", shell->index_of_pipes - 1); */
		close_fds(shell->fd[shell->index_of_pipes - 1]);
	}
	else if (is_last_pipe_command(tmp))
	{
		/* fprintf(stderr, "je last close fd[%d]\n", shell->index_of_pipes - 1); */
		close_fds(shell->fd[shell->index_of_pipes - 1]);
		shell->valid_pipe = 0;
		shell->last_index = -1;
	}
	/* fprintf(stderr, "last pipe for %s is %d\n", tmp->cmd[0], is_last_pipe_command(tmp)); */
	if (is_and_or(map->cmd[0]))
		wait_pid_mono(shell, shell->index_of_commands);
	else
	{
		if (is_last_command(shell->tree->start, tmp))
			wait_pids_bonus(shell->pid, shell,
				shell->index_of_commands, shell->index_of_pid);
	}
	map->err_code = g_err;
	clean_node(tmp);
	shell->index_of_commands++;
	return (execution_bonus(shell, map));
}

t_branch *t_branchcpy(t_branch *map)
{
	t_branch *tmp;

	tmp = malloc(sizeof(t_branch));
	tmp->subshell = map->subshell;
	tmp->dad = NULL;
	return (tmp);
}

int	execution_bonus(t_shell *shell, t_branch *map)
{
	t_branch	*tmp;

	tmp = NULL;
	if (map && map->cmd_block > 0)
	{
		tmp = t_branchcpy(map);
		execute_subshell(shell, tmp);
		if (shell->index_of_pipes != shell->nb_of_pipes && shell->valid_pipe)
		{
			/* fprintf(stderr, "sub: je close fd[%d]\n", shell->index_of_pipes - 1); */
			close_fds(shell->fd[shell->index_of_pipes - 1]);
		}
		else if (is_last_pipe_command(map))
		{
			/* fprintf(stderr, "sub: je last close fd[%d]\n", shell->index_of_pipes - 1); */
			close_fds(shell->fd[shell->index_of_pipes - 1]);
			shell->valid_pipe = 0;
			shell->last_index = -1;
		}
		free(tmp);
		tmp = map;
		map = map->dad;
		if (is_and_or(map->cmd[0]))
			wait_pid_mono(shell, shell->index_of_commands);
		else
			if (is_last_pipe_command(tmp))
				wait_pids_bonus(shell->pid, shell,
					shell->index_of_commands, shell->index_of_pid);
		fprintf(stderr, "le code d'erreur est a la sortie = %d\n", g_err);
		map->err_code = g_err;
		clear_toklst(tmp->subshell);	
		free(tmp->subshell);
		clear_toklst(tmp->left_command);	
		free(tmp->left_command);
		clear_toklst(tmp->right_command);	
		free(tmp->right_command);
		clean(tmp, map);
		shell->index_of_commands++;
		execution_bonus(shell, map);
	}
	else if (map && map->left)
		execute_map_left(shell, map);
	else if (map && map->right)
	{
		execute_map_right(shell, map, tmp);
	}
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
