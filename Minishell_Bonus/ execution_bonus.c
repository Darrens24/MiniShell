/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    execution_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:55:45 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/25 17:11:02 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin_command_bonus(char **command)
{
	if (ft_strncmp(command[0], "pwd", 4) == 0
		|| ft_strncmp(command[0], "cd", 3) == 0
		|| ft_strncmp(command[0], "export", 7) == 0
		|| ft_strncmp(command[0], "env", 4) == 0
		|| ft_strncmp(command[0], "unset", 6) == 0
		|| ft_strncmp(command[0], "exit", 5) == 0
		|| ft_strncmp(command[0], "echo", 5) == 0)
		return (TRUE);
	return (FALSE);
}

void	reset_pipes(t_shell *shell)
{
	shell->nb_of_pipes = 0;
	shell->index_of_pipes = 0;
	shell->last_index = -1;
}

void	changefds(t_shell *shell, int i)
{
	int	**fd;
	int	index;

	index = -1;
	fd = malloc(sizeof(int *) * (i - 1));
	if (fd)
		return (EXIT_FAILURE);
	while (++index < i - 1)
		fd[index] = malloc(sizeof(int) * 2);
	index = -1;
	while (++index < shell->nb_of_pipes - 1)
	{
		fd[index][0] = shell->fd[index][0];
		fd[index][1] = shell->fd[index][1];
	}
	index = -1;
	while (++index < shell->nb_of_pipes - 1)
	{
		free(shell->fd[index][1]);
		free(shell->fd[index][0]);
		free(shell->fd[index]);
	}
	free(shell->fd); // peut etre a supp
	shell->fd = fd;
}

void	checkfds(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->fd[i])
		i++;
	if (--i != shell->nb_of_pipes)
		changefds(shell, i);
}

int	redirection_bonus(t_shell *shell)
{
	checkfds(shell);
	if (shell->index_of_pipes != shell->last_index)
	{
		if (shell->index_of_pipes < shell->nb_of_pipes)
			early_out_redirection(shell->fd[shell->index_of_pipes]);
		if (shell->index_of_pipes != 0)
			inside_redirection(shell->fd[shell->index_of_pipes - 1]);
		if (shell->out == TRUE
			&& shell->index_of_pipes == shell->nb_of_pipes)
			dup2(shell->outfile, STDOUT_FILENO);
	}
	shell->last_index = shell->index_of_pipes;
	return (EXIT_SUCCESS);
}

int	execute_command_clean_leaf(t_shell *shell, char **command)
{
	char		*tmp;
	struct stat	buff;

	stat(command, &buff);
	if (!is_builtin_command_bonus(command))
	{
		if (access(command, F_OK) == 0 && S_ISREG(buff.st_mode))
			tmp = ft_strdup(command);
	//	else
	//		tmp = find_path_bonus();
		if (!tmp)
		{
			if (index > 0)
				close_fds(shell->fd[shell->index_of_pipes - 1]);
			return (EXIT_FAILURE);
		}
		shell->pid[shell->index_of_commands++] = fork();
		signal(SIGINT, &do_nothing);
		signal(SIGQUIT, &do_nothing);
		if (shell->pid[shell->index_of_pipes])
		{
			redirection_bonus(shell);
			execve(tmp, command, shell->array_env);
		}
	}
	//else
	//{
	//	
//	}
	if (shell->index_of_pipes > 0)
		close_fds(shell->fd[shell->index_of_pipes - 1]);
	if (shell->nb_of_pipes == shell->index_of_pipes)
		reset_pipes(shell);
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
