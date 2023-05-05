/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/30 10:24:16 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	slash_manager(t_shell *shell, int index)
{
	int			access_return;
	struct stat	buff;

	access_return = 0;
	if (shell->multi_cmd[index][0][0] == '/')
	{
		access_return = access(shell->multi_cmd[index][0], X_OK);
		if (access_return < 0)
		{
			g_err = 126;
			printf("%s : Permission denied\n", shell->multi_cmd[index][0]);
			return (EXIT_FAILURE);
		}
		stat(shell->multi_cmd[index][0], &buff);
		if (S_ISDIR(buff.st_mode))
		{
			g_err = 126;
			printf("%s : Is a directory\n", shell->multi_cmd[index][0]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	execute_commands(int index, t_shell *shell)
{
	char		*temp;
	struct stat	buff;

	stat(shell->multi_cmd[index][0], &buff);
	temp = NULL;
	if (!ft_strncmp(shell->multi_cmd[0][0], ".", 2) && !shell->multi_cmd[0][1])
		return (printf(DOT));
	if (!is_builtin_command(shell, index))
		execute_execve(shell, temp, buff, index);
	else
		builtin_manager(shell, index);
	if (index > 0)
		close_fds(shell->fd[index - 1]);
	return (EXIT_SUCCESS);
}

int	final_redirection(t_shell *shell)
{
	if (shell->out == TRUE)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		shell->out = FALSE;
	}
	dup2(shell->saved_stdin, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int	pipe_command(t_shell *shell)
{
	int			index;

	get_array_cmd_and_pipe_fds(shell);
	shell->array_env = get_array_env(shell);
	shell->home = ft_strdup(get_home(shell->array_env));
	index = -1;
	while (shell->user_command->nb_elem != 0
		&& ++index < get_number_of_commands(shell))
	{
		if (index < get_number_of_commands(shell) - 1)
			if (pipe(shell->fd[index]) < 0)
				return (printf("Pipe failed\n"));
		execute_commands(index, shell);
	}
	wait_pids(shell->pid, shell);
	final_redirection(shell);
	clean_between_cmds(shell);
	return (EXIT_SUCCESS);
}
