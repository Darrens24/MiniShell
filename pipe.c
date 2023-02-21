/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/21 16:58:09 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

	temp = NULL;
	if (!is_builtin_command(shell, index))
	{
		if (access(shell->multi_cmd[index][0], F_OK) == 0)
			temp = ft_strdup(shell->multi_cmd[index][0]);
		else
			temp = find_path(index, shell);
		if (!temp)
			return (EXIT_FAILURE);
		shell->pid[index] = fork();
		if (shell->pid[index] == 0)
		{
			redirection_parsing(shell, index);
			execve(temp, shell->multi_cmd[index], shell->array_env);
		}
		free(temp);
	}
	else
		builtin_manager(shell, index);
	if (index > 0)
		close_fds(shell->fd[index - 1]);
	return (EXIT_SUCCESS);
}

int	final_redirection(t_shell *shell)
{
	if (shell->out == true)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		shell->out = false;
	}
	dup2(shell->saved_stdin, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int	pipe_command(t_shell *shell)
{
	int	i;

	get_array_cmd_and_pipe_fds(shell);
	shell->array_env = get_array_env(shell);
	shell->home = ft_strdup(get_home(shell->array_env));
	i = -1;
	while (shell->user_command->nb_elem != 0
		&& ++i < get_number_of_commands(shell))
	{
		if (i < get_number_of_commands(shell) - 1)
			if (pipe(shell->fd[i]) < 0)
				return (printf("Pipe failed\n"));
	//	if (redirect_and_execute_cmd(shell, i) != 0)
	//		return (EXIT_FAILURE);
		redirect_and_execute_cmd(shell, i);
	}
	wait_pids(shell->pid);
	final_redirection(shell);
	clean_between_cmds(shell);
	return (EXIT_SUCCESS);
}
