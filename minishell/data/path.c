/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:40:44 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/23 12:21:09 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_err = 0;

char	*find_path(int index, t_shell *shell)
{
	char	*temp;
	char	*all_path;

	all_path = get_path(shell->array_env);
	if (!all_path)
	{
		return (printf("%s : Command not found\n",
				shell->multi_cmd[index][0]), NULL);
	}
	shell->all_path = ft_split_slash(all_path, ':');
	if (!shell->all_path[0])
		return (NULL);
	temp = get_correct_path(shell, index);
	free_array(shell->all_path);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*get_path(char **array_env)
{
	int	i;

	i = 0;
	while (array_env[i])
	{
		if (ft_strncmp(array_env[i], "PATH=", 5) == 0)
			return (array_env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_correct_path(t_shell *shell, int index)
{
	int	i;

	shell->correct_path = NULL;
	i = -1;
	while (shell->all_path[++i])
	{
		shell->correct_path = ft_strjoin(shell->all_path[i],
				shell->multi_cmd[index][0]);
		if (access(shell->correct_path, F_OK) == 0)
			return (shell->correct_path);
		free(shell->correct_path);
	}
	g_err = 127;
	printf("%s : Command not found\n", shell->multi_cmd[index][0]);
	return (NULL);
}
