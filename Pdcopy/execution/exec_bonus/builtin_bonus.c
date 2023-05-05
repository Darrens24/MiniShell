/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:01:19 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/04 20:29:46 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtin_bonus(t_shell *shell, char **command, int pipe)
{
	/* execute_directory_cmd(shell, i); */
	if (ft_strncmp(command[0], "exit", 5) == 0)
		exit_shell(shell);
	if (ft_strncmp(command[0], "env", 4) == 0)
	{
		if (command[1])
			return (printf("Env command won't take arguments or options\n"));
		print_list(shell->env_l);
	}
	/* else if (ft_strncmp(command[0], "export", 7) == 0) */
	/* 	export_manager(shell, i); */
	else if (ft_strncmp(command[0], "unset", 6) == 0)
	{
		if (argument_after_cmd(shell) == FALSE)
			return (EXIT_SUCCESS);
		else
			return (unset_variable(shell));
	}
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		print_echo(command, shell);
	return (EXIT_SUCCESS);
}

int	builtin_manager_bonus(t_shell *shell, char **command, int is_pipe)
{
	if (shell->index_of_pipes != shell->nb_of_pipes)
		pipe(shell->fd[shell->index_of_pipes]);
	shell->pid[shell->index_of_commands] = fork();
	if (shell->pid[shell->index_of_commands] == 0)
	{
		redirection_bonus(shell);
		execute_builtin_bonus(shell, command, is_pipe);
		exit(1);
	}
	if (shell->index_of_pipes != shell->nb_of_pipes)
		shell->last_index = shell->index_of_pipes;
	return (EXIT_SUCCESS);
}