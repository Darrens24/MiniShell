/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/22 16:29:39 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_directory(t_shell *shell, const char *path)
{
	shell->previous_dir_path = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		g_err = 1;
		return (perror("chdir"), EXIT_FAILURE);
	}
	shell->current_dir_path = getcwd(NULL, 0);
	return (EXIT_SUCCESS);
}

int	go_to_home_directory(t_shell *shell)
{
	shell->previous_dir_path = getcwd(NULL, 0);
	if (change_directory(shell, shell->home) != 0)
		return (EXIT_FAILURE);
	shell->current_dir_path = getcwd(NULL, 0);
	return (EXIT_SUCCESS);
}

int	go_to_previous_directory(t_shell *shell)
{
	if (change_directory(shell, shell->previous_dir_path) != 0)
		return (EXIT_FAILURE);
	print_pwd_linux(shell);
	return (EXIT_SUCCESS);
}

int	execute_directory_cmd(t_shell *shell, int i)
{
	if (ft_strncmp(shell->multi_cmd[i][0], "cd", 3) == 0)
	{
		if ((!shell->multi_cmd[i][1])
			|| ft_strncmp(shell->multi_cmd[i][1], "~", 2) == 0
			|| ft_strncmp(shell->multi_cmd[i][1], "~/", 3) == 0)
			return (go_to_home_directory(shell));
		else if (ft_strncmp(shell->multi_cmd[i][1], "-", 2) == 0)
			return (go_to_previous_directory(shell));
		return (change_directory(shell, shell->multi_cmd[i][1]));
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "pwd", 4) == 0)
		return (print_pwd_linux(shell));
	return (EXIT_FAILURE);
}

int	print_pwd_linux(t_shell *shell)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	if (!directory)
	{
		while (!directory)
		{
			change_directory(shell, "../");
			directory = getcwd(NULL, 0);
		}
	}
	ft_putendl_fd(directory, STDOUT_FILENO);
	free(directory);
	directory = NULL;
	return (EXIT_SUCCESS);
}
