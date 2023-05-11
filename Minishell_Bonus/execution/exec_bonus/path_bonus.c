/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:59:31 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 11:09:12 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_correct_path_bonus(t_shell *shell, char *command)
{
	int			i;
	struct stat	buff;

	stat(command, &buff);
	shell->correct_path = NULL;
	i = -1;
	while (shell->all_path[++i] && (ft_strlen(command) > 0
			&& !S_ISDIR(buff.st_mode)))
	{
		shell->correct_path = ft_strjoin(shell->all_path[i],
				command);
		if (access(shell->correct_path, F_OK) == 0)
			return (shell->correct_path);
		free(shell->correct_path);
	}
	g_err = 127;
	if (ft_strncmp(".", command, 1) == 0)
		printf("%s: No such file or directory\n", command);
	else
		printf("%s: Command not found\n", command);
	return (NULL);
}

char	*find_path_bonus(char *command, t_shell *shell)
{
	char	*temp;
	char	*all_path;

	all_path = get_path(shell->array_env);
	if (!all_path)
	{
		return (printf("%s : Command not found\n",
				command), NULL);
	}
	shell->all_path = ft_split_slash(all_path, ':');
	if (!shell->all_path[0])
		return (NULL);
	temp = get_correct_path_bonus(shell, command);
	free_array(shell->all_path);
	if (!temp)
		return (NULL);
	return (temp);
}

int	printdot(void)
{
	g_err = 2;
	return (printf(DOT));
}

int	slash_manager_bonus(char **command)
{
	int			access_return;
	struct stat	buff;

	access_return = access(command[0], F_OK);
	if (command[0][0] == '/'
		|| command[0][0] == '.')
		if (access_return < 0)
			return (printnoaccess(command));
	stat(command[0], &buff);
	if (!ft_strncmp(command[0], ".", 2) && !command[1])
		return (printdot());
	if (S_ISDIR(buff.st_mode))
	{
		g_err = 126;
		printf("%s : Is a directory\n", command[0]);
		return (EXIT_FAILURE);
	}
	if (!check_permission_bonus(access_return, command))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_permission_bonus(int access_return, char **command)
{
	access_return = access(command[0], X_OK);
	if (command[0][0] == '.')
	{
		if (access_return < 0)
		{
			g_err = 126;
			printf("%s : Permission denied\n", command[0]);
			return (FALSE);
		}
	}
	return (TRUE);
}
