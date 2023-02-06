/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/06 16:26:33 by eleleux          ###   ########.fr       */
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

	temp = get_correct_path(shell, index);
	if (temp == NULL)
		return (EXIT_FAILURE);
	shell->pid[index] = fork();
	if (shell->pid[index] == 0)//on est dans le process fils
	{
		if (index < (get_number_of_commands(shell) - 1))
			first_out_redirection(shell->fd[index]);
		if (index != 0)
			inside_redirection(shell->fd[index - 1]);
		//if (is_outfile_redirection(shell->user_command) && index == get_number_of_commands(shell) - 1)
		//	outfile_redirection_parsing(shell);
		execve(temp, shell->multi_cmd[index], shell->array_env);
	}
	if (index != 0)
	{
		close(shell->fd[index - 1][0]);
		close(shell->fd[index - 1][1]);
	}
	free(temp);
	return (EXIT_SUCCESS);
}

int	pipe_command(t_shell *shell)
{
	int		i = 0;

	if (infile_redirection_parsing(shell) != 0)
		return (EXIT_FAILURE);
	get_array_cmd_and_pipe_fds(shell);
	i = -1;
	while (shell->user_command->nb_elem != 0 && ++i < get_number_of_commands(shell))
		redirect_and_execute_cmd(shell, i);
	wait_pids(shell->pid);
	close_fds(shell->fd);
	free(shell->pid);
	i = -1;
	while (++i < (get_number_of_commands(shell) - 1))
		free(shell->fd[i]);
	free(shell->fd);
	dup2(shell->saved_stdin, STDIN_FILENO);
	return (EXIT_SUCCESS);
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
