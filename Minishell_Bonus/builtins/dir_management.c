/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/23 13:53:45 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_directory(t_shell *shell, const char *path)
{
	shell->previous_dir_path = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		g_err = 1;
		free(shell->previous_dir_path);
		return (perror("chdir"), EXIT_FAILURE);
	}
	shell->current_dir_path = getcwd(NULL, 0);
	if (shell->current_dir_path)
	{
		update_pwd(shell, shell->env_l);
		update_pwd(shell, shell->sorted_env_l);
		free(shell->current_dir_path);
	}
	if (shell->previous_dir_path)
	{
		update_oldpwd(shell, shell->env_l);
		update_oldpwd(shell, shell->sorted_env_l);
		free(shell->previous_dir_path);
	}
	return (EXIT_SUCCESS);
}

int	go_to_home_directory(t_shell *shell)
{
	if (change_directory(shell, shell->home) != 0)
	{
		free(shell->previous_dir_path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	go_to_previous_directory(t_shell *shell)
{
	if (!shell->previous_dir_path)
		return (print_pwd_linux(shell));
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
			free(directory);
			change_directory(shell, "../");
			directory = getcwd(NULL, 0);
		}
	}
	ft_putendl_fd(directory, STDOUT_FILENO);
	free(directory);
	directory = NULL;
	return (EXIT_SUCCESS);
}
