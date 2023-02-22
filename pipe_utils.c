/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:12:25 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/22 17:23:40 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_err;

t_tok	*go_to_next_pipe(t_shell *shell, t_tok *tok, int index) // A Remplacer par go_to_next delimiter avec tous les cas de separation de commande
{
	int	i;

	tok = shell->user_command->start;
	i = 0;
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

int	early_out_redirection(int *fd)
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

// waitpid envoie l'erreur dans la variable globale
// quand waitpid est > 0, c'est qu'il

int	error_func(int error_code)
{
	//printf("wifstopped = %d\n", WIFSTOPPED(error_code));
	//printf("wifsignaled = %d\n", WIFSIGNALED(error_code));
	//printf("wtermsig = %d\n", WTERMSIG(error_code));
	if (WTERMSIG(error_code) == 2)
		g_err = 130;
	else if (WTERMSIG(error_code) == 3)
		g_err = 131;
	else if (WTERMSIG(error_code) == 11)
	{
		g_err = 139;
		printf("Segmentation fault\n");
	}
	else if (WTERMSIG(error_code) == 10)
	{
		g_err = 138;
		printf("Bus error\n");
	}
	else if (WTERMSIG(error_code) == 6)
	{
		g_err = 134;
		printf("Pointer being freed was not allocated\n");
	}
	//printf("stopsig = %d\n", WSTOPSIG(error_code));
	//printf("stopsig = %d\n", WSTOPSIG(error_code));
	else
		g_err = WEXITSTATUS(error_code);
	return (EXIT_SUCCESS);
}

int	wait_pids(pid_t *pid)
{
	int	i;
	int	waitpid_return;
	int	error_code;

	i = -1;
	error_code = 0;
	while (pid[++i])
	{
		waitpid_return = waitpid(pid[i], &error_code, 0);
		if (waitpid_return > 0) 
			error_func(error_code);
	}
	return (EXIT_SUCCESS);
}

int	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (EXIT_SUCCESS);
}
