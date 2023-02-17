/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/17 09:53:43 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_number_of_commands(t_shell *shell)
{
	t_tok	*temp;
	int		nb_of_cmd;

	nb_of_cmd = 1;
	temp = shell->user_command->start;
	while (temp)
	{
		if (ft_strncmp(temp->var, "|", 2) == 0 && temp->quote == 0)
			nb_of_cmd++;
		temp = temp->next;
	}
	return (nb_of_cmd);
}

int	redirection_parsing(t_shell *shell, int index)
{
	//shell->saved_stdout = dup(STDOUT_FILENO);
	if (index < (get_number_of_commands(shell) - 1))
		early_out_redirection(shell->fd[index]);
	if (index != 0)
		inside_redirection(shell->fd[index - 1]);
	if (shell->out == true && index == get_number_of_commands(shell) - 1)
		dup2(shell->outfile, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	builtin_manager(t_shell *shell, int index)
{
	if (get_number_of_commands(shell) == 1)
	{
		redirection_parsing(shell, index);
		execute_builtin_cmd(shell, index);
	}
	else if (get_number_of_commands(shell) > 1)
	{
		shell->pid[index] = fork();
		if (shell->pid[index] == 0)
		{
			redirection_parsing(shell, index);
			execute_builtin_cmd(shell, index);
			exit(1);
		}
	}
	return (EXIT_SUCCESS);
}

int	redirect_and_execute_cmd(t_shell *shell, int index)
{
	char	*temp;
	char	*all_path;

	temp = NULL;
	if (!is_builtin_command(shell, index))
	{
		shell->array_env = get_array_env(shell);
		all_path = get_path(shell->array_env);
		if (!all_path)
			return (EXIT_FAILURE);
		shell->all_path = ft_split_slash(all_path, ':');
		if (!shell->all_path[0])
			return (EXIT_FAILURE);
		temp = get_correct_path(shell, index);
		if (!temp)
			return (EXIT_FAILURE);
		shell->pid[index] = fork();
		if (shell->pid[index] == 0)
		{
			redirection_parsing(shell, index);
			execve(temp, shell->multi_cmd[index], shell->array_env);
		}
		free_array(shell->all_path);
		free_array(shell->array_env);
		free(temp);
	}
	else
		builtin_manager(shell, index);
	if (index > 0)
		close_fds(shell->fd[index - 1]);
	return (EXIT_SUCCESS);
}

int	pipe_command(t_shell *shell)
{
	int	i;

	shell->saved_stdout = dup(STDOUT_FILENO);
	get_array_cmd_and_pipe_fds(shell);
	i = -1;
	while (shell->user_command->nb_elem != 0 && ++i < get_number_of_commands(shell))
	{
		if (i < get_number_of_commands(shell) - 1)
		{
			if (pipe(shell->fd[i]) < 0)
				return (printf("Pipe failed\n"));
		}
		if (redirect_and_execute_cmd(shell, i) != 0)
			return (EXIT_FAILURE);
	}
	if (shell->out == true)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		shell->out = false;
	}
	dup2(shell->saved_stdin, STDIN_FILENO);
	wait_pids(shell->pid);
	if (shell->multi_cmd)
	{
		while (i < get_number_of_commands(shell) && shell->multi_cmd)
		{
			free_array(shell->multi_cmd[i]);
			i++;
		}
		free(shell->multi_cmd);
	}
	if (get_number_of_commands(shell) > 1)
		free_pids_fds(shell);
	return (EXIT_SUCCESS);
}

void	free_pids_fds(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < (get_number_of_commands(shell) - 1))
		free(shell->fd[i]);
	free(shell->fd);
	free(shell->pid);
}

int	get_array_cmd_and_pipe_fds(t_shell *shell)
{
	int		i;

	shell->pid = malloc(sizeof(int) * get_number_of_commands(shell));
	if (!shell->pid)
		return (EXIT_FAILURE);
	i = -1;
	shell->fd = malloc(sizeof(int *) * (get_number_of_commands(shell) - 1));
	if (!shell->fd)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < (get_number_of_commands(shell) - 1))
	{
		shell->fd[i] = malloc(sizeof(int) * 2);
		if (!shell->fd[i])
			return (EXIT_FAILURE);
	}
	shell->multi_cmd = malloc(sizeof(char *) * (get_number_of_commands(shell) + 1));
	if (!shell->multi_cmd)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < get_number_of_commands(shell))
		shell->multi_cmd[i] = get_command_in_tok(shell, i);
	shell->multi_cmd[i] = NULL;
	return (EXIT_SUCCESS);
}
