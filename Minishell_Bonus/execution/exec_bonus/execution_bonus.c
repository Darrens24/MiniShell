/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:55:45 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/10 09:00:08 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin_command_bonus(char **command)
{
	if (ft_strncmp(command[0], "pwd", 4) == 0
		|| ft_strncmp(command[0], "cd", 3) == 0
		|| ft_strncmp(command[0], "export", 7) == 0
		|| ft_strncmp(command[0], "env", 4) == 0
		|| ft_strncmp(command[0], "unset", 6) == 0
		|| ft_strncmp(command[0], "exit", 5) == 0
		|| ft_strncmp(command[0], "echo", 5) == 0)
		return (TRUE);
	return (FALSE);
}

int	redirection_bonus(t_shell *shell)
{	
	if (shell->index_of_pipes < shell->nb_of_pipes)
		early_out_redirection(shell->fd[shell->index_of_pipes]);
	if (shell->last_index != -1)
		inside_redirection(shell->fd[shell->index_of_pipes - 1]);
	return (EXIT_SUCCESS);
}

int	execute_command_clean_leaf(t_shell *shell, char **command, int pipe)
{
	char		*tmp;
	struct stat	buff;

	tmp = NULL;
	stat(command[0], &buff);
	if (slash_manager_bonus(command))
		return (EXIT_FAILURE);
	if (!is_builtin_command_bonus(command))
		not_execute_builtin(shell, command, tmp, buff);
	else
	{
		if (ft_strncmp(command[0], "export", 7) == 0)
			export_b_manager(shell, command, pipe);
		else if (ft_strncmp(command[0], "unset", 6) == 0)
		{
			if (!command[1] || pipe)
				return (EXIT_SUCCESS);
			else
				return (unset_b_variable(shell, command));
		}
		else
			builtin_manager_bonus(shell, command, pipe);
	}
	return (EXIT_SUCCESS);
}
