/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:01:19 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/11 15:48:53 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin_bonus(t_shell *shell, char **command, int pipe)
{
	if (ft_strncmp(command[0], "env", 4) == 0)
	{
		if (command[1])
			return (printf("Env command won't take arguments or options\n"));
		print_list(shell->env_l);
	}
	else if (ft_strncmp(command[0], "export", 7) == 0)
		export_b_manager(shell, command, pipe);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
	{
		if (!command[1] || pipe)
			return (EXIT_SUCCESS);
		else
			return (unset_b_variable(shell, command));
	}
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		print_b_echo(command, shell);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (print_pwd_linux(shell));
	return (EXIT_SUCCESS);
}

int	builtin_manager_bonus(t_shell *shell, char **command, int is_pipe)
{
	execute_b_directory_cmd(shell, command, is_pipe);
	if (shell->index_of_pipes != shell->nb_of_pipes)
		pipe(shell->fd[shell->index_of_pipes]);
	shell->pid[shell->index_of_commands] = fork();
	if (shell->pid[shell->index_of_commands] == 0)
	{
		redirection_bonus(shell);
		execute_builtin_bonus(shell, command, is_pipe);
		exit(g_err);
	}
	if (shell->index_of_pipes != shell->nb_of_pipes)
		shell->last_index = shell->index_of_pipes;
	return (EXIT_SUCCESS);
}
