/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/11 15:48:32 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_b_directory_cmd(t_shell *shell, char **command, int pipe)
{
	if (ft_strncmp(command[0], "cd", 3) == 0)
	{
		if (pipe)
			return (EXIT_SUCCESS);
		else if ((!command[1])
			|| ft_strncmp(command[1], "~", 2) == 0
			|| ft_strncmp(command[1], "~/", 3) == 0)
			return (go_to_home_directory(shell));
		else if (ft_strncmp(command[1], "-", 2) == 0)
			return (go_to_previous_directory(shell));
		return (change_directory(shell, command[1]));
	}
	return (EXIT_FAILURE);
}
