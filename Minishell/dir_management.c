/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/07 14:07:35 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_directory_cmd(t_shell *shell, int i)
{
	if (ft_strncmp(shell->multi_cmd[i][0], "pwd", 4) == 0)
		return (print_pwd_linux());
	else if (ft_strncmp(shell->multi_cmd[i][0], "cd", 3) == 0)
	{
		if (!shell->multi_cmd[i][1])
			return (change_directory("/home/xq/Documents/42/commun-core/Minishell"));
		return (change_directory(shell->multi_cmd[i][1]));
	}
	return (EXIT_FAILURE);
}

int	print_pwd_linux(void)
{
	char	*directory;
		
	directory = getcwd(NULL, 0);
	if (!directory)
	{
		while (!directory)
		{
			change_directory("../");
			directory = getcwd(NULL, 0);
		}
	}
	ft_putendl_fd(directory, STDOUT_FILENO);
	free(directory);
	directory = NULL;
	return (EXIT_SUCCESS);
}

int	change_directory(const char *path)
{
	if (chdir(path) < 0)
		return (perror("chdir"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
