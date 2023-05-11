/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:42:26 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/23 13:47:39 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *line, int start, int end)
{
	int		i;
	char	*str;

	if (!line)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char) * (end - start) + 1);
	if (!str)
		return (NULL);
	while (start != end && line[start])
	{
		str[i] = line[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlenequal(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	return (i);
}

int	argument_after_cmd(t_shell *shell)
{
	if (shell->user_command->nb_elem > 1)
		return (1);
	return (0);
}

int	option_n(char **command, int i)
{
	int		returnval;
	size_t	x;

	returnval = 0;
	x = 1;
	i++;
	if (command[i] && command[i][0] && command[i][0] == '-')
	{
		while (command[i][x] && command[i][x] == 'n')
			x++;
		if (x == ft_strlen(command[i]) && x != 1)
			returnval = 1;
	}
	return (returnval);
}

int	option_njump(char **command, int i)
{
	size_t	x;

	i++;
	while (command[i] && command[i][0] && command[i][0] == '-')
	{
		x = 1;
		while (command[i][x] && command[i][x] == 'n')
			x++;
		if (x == 1 || x != ft_strlen(command[i]))
			break ;
		i++;
	}
	return (i);
}
