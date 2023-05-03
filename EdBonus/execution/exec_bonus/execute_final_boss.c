/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_final_boss.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:09:18 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/02 19:11:13 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* int	subshell(t_shell *shell, char **command, char *tmp, */
/* 	struct stat buff) */
/* { */
/* 	if (shell->index_of_pipes != shell->nb_of_pipes) */
/* 		pipe(shell->fd[shell->index_of_pipes]); */
/* 	shell->pid[shell->index_of_commands] = fork(); */
/* 	signal(SIGINT, &do_nothing); */
/* 	signal(SIGQUIT, &do_nothing); */
/* 	if (shell->pid[shell->index_of_commands] == 0) */
/* 	{ */
/* 		redirection_bonus(shell); */
/* 		execve(tmp, command, shell->array_env); */
/* 	} */
/* 	if (shell->index_of_pipes != shell->nb_of_pipes) */
/* 		shell->last_index = shell->index_of_pipes; */
/* 	free(tmp); */
/* 	return (EXIT_SUCCESS); */
/* } */

int	execute_subshell(t_shell *shell, t_branch *map)
{
	pid_t		pid;
	t_branch	*tmp;
	int			waitpid_return;
	int			error_code;
	
	waitpid_return = 0;
	error_code = 0;
	tmp = map;
	shell->current_cmdb = map->cmd_block;
	if (shell->index_of_pipes != shell->nb_of_pipes)
	{
		printf("je pipe dans subshell\n");
		pipe(shell->fd[shell->index_of_pipes]);
	}
	redirection_bonus(shell);
	pid = fork();
	if (pid == 0)
	{
		tmp->dad = NULL;
		execution_bonus(shell, tmp);
		printf("JE TERMINE L'EXECUTION DU SUB\n");
		exit(0);
	}
	waitpid_return = waitpid(pid, &error_code, 0);
	if (waitpid_return > 0)
		error_func(error_code);
	map->err_code = g_err;
	tmp = map;
	map = map->dad;
	return	(clean(tmp, map), execution_bonus(shell, map));
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
				return (clean(tmp->right, tmp), execution_bonus(shell, map));
			else if (!map)
				return (clean(shell->tree->start, map), EXIT_SUCCESS);
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

int	execute_map_operator(t_shell *shell, t_branch *map, t_branch *tmp)
{
	if (shell->index_of_pipes != shell->nb_of_pipes && map->cmd_block == 0)
	{
		printf("je pipe dans operator\n");
		pipe(shell->fd[shell->index_of_pipes]);
	}
	shell->current_cmdb = map->cmd_block;
	execute_command_clean_leaf(shell, tmp->cmd);
	if ((map && shell->nb_of_pipes != shell->index_of_pipes)
		|| (shell->last_index != -1 && shell->valid_pipe))
	{
		if (is_last_pipe_command(tmp) || map->err_code > 0)
			close_fds(shell->fd[shell->index_of_pipes - 1]);
		if (is_last_pipe_command(tmp))
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
	{
		wait_pids_bonus(shell->pid, shell,
			shell->index_of_commands, shell->index_of_pid);
		//close_fds(shell->fd[shell->index_of_pipes - 1]);
	}
	clean_node(tmp);
	map->err_code = g_err;
	shell->index_of_commands++;
	return (execution_bonus(shell, map));
}

// ls && (wc && wc) || (whoami && lol)
int	execution_bonus(t_shell *shell, t_branch *map)
{
	t_branch	*tmp;
	static int	cmd_block = 0;

	tmp = NULL;
	if (map->cmd_block > cmd_block && map->cmd_block != 0)
	{
		// SI ON EST DANS UNE PIPE (MAP DAD), ON FAIT LA REDIRECTION OUT //
		printf("JE FAIS UN SUBSHELL\n");
		cmd_block = map->cmd_block;
		execute_subshell(shell, map);
		print_cmds_with_blocks(shell->tree->start);
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