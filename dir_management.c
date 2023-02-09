/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/09 16:29:30 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(char **envp)
{
	int	i;

	i = 0;
	while (envp && ft_strncmp(envp[i], "HOME=", 5))
		i++;
	return (envp[i] + 5);
}

int	go_to_home_directory(t_shell *shell)
{
	if (change_directory(shell->home) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute_directory_cmd(t_shell *shell, int i)
{
	if (ft_strncmp(shell->multi_cmd[i][0], "cd", 3) == 0)
	{
		if (shell->multi_cmd[i][2] != NULL)
			return (printf("Too much arguments for cd\n"));
		else if ((!shell->multi_cmd[i][1])
			|| ft_strncmp(shell->multi_cmd[i][1], "~", 2) == 0
			|| ft_strncmp(shell->multi_cmd[i][1], "~/", 3) == 0)
				return (go_to_home_directory(shell));
		return (change_directory(shell->multi_cmd[i][1]));
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "pwd", 4) == 0)
		return (print_pwd_linux());
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
