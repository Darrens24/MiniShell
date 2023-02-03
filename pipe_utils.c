/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:12:25 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/03 10:48:53 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*go_to_next_pipe(t_shell *shell, t_tok *tok, int index) // A Remplacer par go_to_next delimiter avec tous les cas de separation de commande
{
	int	i = 0;
	tok = shell->user_command->start;

	while (tok && i < index)
	{
		while (tok && ft_strncmp(tok->var, "|", 2) != 0)
			tok = tok->next;
		if (tok->next)
			tok = tok->next;
		i++;
	}
	return (tok);
}

int	first_out_redirection(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	return (EXIT_SUCCESS);
}

int	inside_redirection(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (EXIT_SUCCESS);
}

int	wait_pids(pid_t *pid)
{
	int	i;

	i = -1;
	while (pid[++i])
		waitpid(pid[i], 0, 0);
	return (EXIT_SUCCESS);
}

int	close_fds(int **fd)
{
	int	i;

	i = -1;
	while (fd[++i])
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	return (EXIT_SUCCESS);
}


