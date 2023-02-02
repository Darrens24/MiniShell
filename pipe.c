/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/02 13:55:07 by eleleux          ###   ########.fr       */
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

int	redirect_pipe_execute_cmd(pid_t *pid, int **fd, t_shell *shell, int index)
{
	char	*temp = get_correct_path(shell, index);
	if (temp == NULL)
		return (EXIT_FAILURE);
	/*printf("cmdarg1 = %s\n", shell->multi_cmd[index][0]);
	printf("cmdarg2 = %s\n", shell->multi_cmd[index][1]);
	printf("path = %s\n", temp);
	printf("nb of cmd = %d\n", get_number_of_commands(shell));*/
	
	pid[index] = fork();
	if (pid[index] == 0)
	{
		if (index < (get_number_of_commands(shell) - 1))
			first_out_redirection(fd[index]);
		if (index != 0)
			inside_redirection(fd[index - 1]);
		execve(temp, shell->multi_cmd[index], shell->array_env);
	}
	if (index != 0)
	{
		close(fd[index - 1][0]);
		close(fd[index - 1][1]);
	}
	free(temp);
	return (EXIT_SUCCESS);
}

int	pipe_command(t_shell *shell)
{
	pid_t	*pid;
	int		**fd;
	int		i = 0;

	pid = malloc(sizeof(int) * get_number_of_commands(shell));
	if (!pid)
		return (EXIT_FAILURE);
	fd = malloc(sizeof(int *) * (get_number_of_commands(shell) - 1));
	i = 0;
	while (i < (get_number_of_commands(shell) - 1))
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (pipe(fd[i]) < 0)
			return (printf("Pipe failed\n"));
		i++;
	}
	//if (redirection case)
		//change_input;
	i = -1;
	while (++i < get_number_of_commands(shell))
		redirect_pipe_execute_cmd(pid, fd, shell, i);
	wait_pids(pid);
	close_fds(fd);
	//tests
	free(pid);
	i = -1;
	while (++i < (get_number_of_commands(shell) - 1))
		free(fd[i]);
	free(fd);
	return (EXIT_SUCCESS);
}

int	get_pipe_commands(t_shell *shell)
{
	int		i;

	shell->multi_cmd = malloc(sizeof(char *) * (get_number_of_commands(shell) + 1));
	if (!shell->multi_cmd)
		return (EXIT_FAILURE);
	i = 0;
	while (i < get_number_of_commands(shell))
	{
		shell->multi_cmd[i] = get_command_in_tok(shell, i);
		i++;
	}
	shell->multi_cmd[i] = NULL;
	pipe_command(shell); // rajouter envp si ca marche pas
/*	i = 0;
	int	j = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			printf("arg[%d] : %s\n",i, commands[i][j]);
			j++;
		}
		i++;
	}*/
	return (EXIT_SUCCESS);
}
