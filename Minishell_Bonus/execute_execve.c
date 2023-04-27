/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:45:48 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/27 17:47:59 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (EXIT_SUCCESS);
}

int	execute_execve(t_shell *shell, char *temp, struct stat buff, int index)
{
	if (slash_manager(shell, index) != 0)
		return (EXIT_FAILURE);
	if (access(shell->multi_cmd[index][0], F_OK) == 0
		&& S_ISREG(buff.st_mode))
		temp = ft_strdup(shell->multi_cmd[index][0]);
	else
		temp = find_path(index, shell);
	if (!temp)
	{
		if (index > 0)
			close_fds(shell->fd[index - 1]);
		return (EXIT_FAILURE);
	}
	shell->pid[index] = fork();
	signal(SIGINT, &do_nothing);
	signal(SIGQUIT, &do_nothing);
	if (shell->pid[index] == 0)
	{
		redirection_parsing(shell, index);
		execve(temp, shell->multi_cmd[index], shell->array_env);
	}
	free(temp);
	return (EXIT_SUCCESS);
}
