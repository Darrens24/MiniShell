/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:01:19 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/27 17:01:34 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_manager_bonus(t_shell *shell, int index)
{
	shell->pid[index] = fork();
	if (shell->pid[index] == 0)
	{
		redirection_parsing(shell, index);
		execute_builtin_cmd(shell, index);
		exit(1);
	}
	return (EXIT_SUCCESS);
}
