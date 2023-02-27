/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:53:45 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/27 10:58:46 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_asked_wildcards(char *var, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '*' && i != 0 && no_wildcard_before(var, i - 1) == true)
			shell->wild_before = ft_strndup(var, 0, i);
		if (var[i] == '*' && var[i + 1] && string_is_wildcard(var + i + 1))
		{
			shell->wild_middle[j] = get_wild_middle(var, i + 1);
			j++;
		}
		if (var[i] == '*' && var[i + 1] && !string_is_wildcard(var + i + 1))
			shell->wild_after = ft_strndup(var, i + 1, ft_strlen(var));
		i++;
	}
	shell->wild_middle[j] = NULL;
	return (EXIT_SUCCESS);
}

char	*get_wild_middle(char *str, int index)
{
	char	*middle;
	int		start;

	start = index;
	while (str[index] && str[index] != '*')
		index++;
	middle = ft_strndup(str, start, index);
	return (middle);
}

int	get_wildcard_files(t_shell *shell)
{
	char	*buffer;
	int		fd_temp;

	shell->nb_of_sub = 0;
	fd_temp = open(".tmp", O_RDWR, 0644);
	if (fd_temp < 0)
		return (EXIT_FAILURE);
	buffer = ft_calloc(1, 1);
	add_files_to_toklist(buffer, fd_temp, shell);
	if (shell->nb_of_sub != 0)
		remove_wildcard_tok(shell->user_command);
	close(fd_temp);
	unlink(".tmp");
	free_wildcards(shell);
	return (EXIT_SUCCESS);
}

int	compare_middle_wildcard(char *buffer, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->wild_middle[j])
	{
		if (!ft_strnstr((buffer + i), shell->wild_middle[j], ft_strlen(buffer)))
			return (false);
		while (!ft_strncmp(shell->wild_middle[j], buffer + i,
				ft_strlen(shell->wild_middle[j])))
			i++;
		i += ft_strlen(shell->wild_middle[j]);
		j++;
	}
	return (true);
}

int	compare_after_wildcard(char *buffer, t_shell *shell)
{
	int	i;

	i = ft_strlen(buffer) - ft_strlen(shell->wild_after);
	if (ft_strncmp(buffer + i, shell->wild_after,
			ft_strlen(shell->wild_after)) == 0)
		return (true);
	return (false);
}
