/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/07 17:58:40 by eleleux          ###   ########.fr       */
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
		if (ft_strncmp(temp->var, "|", 2) == 0)
			nb_of_cmd++;
		temp = temp->next;
	}
	return (nb_of_cmd);
}

int	redirect_and_execute_cmd(t_shell *shell, int index)
{
	char	*temp;

	if (!is_builtin_command(shell, index))
	{
		temp = get_correct_path(shell, index);
		shell->pid[index] = fork();
		if (shell->pid[index] == 0) // FILS
		{
			if (index < (get_number_of_commands(shell) - 1))
				early_out_redirection(shell->fd[index]);
			if (index != 0)
				inside_redirection(shell->fd[index - 1]);
			if (shell->out == TRUE && index == get_number_of_commands(shell) - 1)
				dup2(shell->outfile, STDOUT_FILENO);
			execve(temp, shell->multi_cmd[index], shell->array_env);
		}
	}
	else
	{
		if (index < (get_number_of_commands(shell) - 1))
			early_out_redirection(shell->fd[index]);
		if (index != 0)
			inside_redirection(shell->fd[index - 1]);
		if (shell->out == TRUE && index == get_number_of_commands(shell) - 1)
			dup2(shell->outfile, STDOUT_FILENO);
		execute_builtin_cmd(shell, index);
	}
	if (index > 0)
	{
		close(shell->fd[index - 1][0]);
		close(shell->fd[index - 1][1]);
	}
	if (!is_builtin_command(shell, index))
		free(temp);
	return (EXIT_SUCCESS);
}

int	pipe_command(t_shell *shell)
{
	int	i;

	get_array_cmd_and_pipe_fds(shell);
	i = -1;
	while (shell->user_command->nb_elem != 0 && ++i < get_number_of_commands(shell))
		redirect_and_execute_cmd(shell, i);
	wait_pids(shell->pid);
	if (shell->out == TRUE)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		shell->out = FALSE;
	}
	dup2(shell->saved_stdin, STDIN_FILENO);
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
	shell->fd = malloc(sizeof(int *) * (get_number_of_commands(shell) - 1));
	if (!shell->fd)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < (get_number_of_commands(shell) - 1))
	{
		shell->fd[i] = malloc(sizeof(int) * 2);
		if (pipe(shell->fd[i]) < 0)
			return (printf("Pipe failed\n"));
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
