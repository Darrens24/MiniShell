/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:53:45 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/18 16:51:45 by eleleux          ###   ########.fr       */
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
	shell->wild_middle[j] = NULL; //peut-etre rajouter une protection
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

char	**get_wildcard_files(t_shell *shell)
{
	char	*buffer;
	int		fd_temp;
	t_tok	*temp;
	
	fd_temp = open(".tmp", O_RDWR, 0644);
	if (fd_temp < 0)
		return (NULL);
	buffer = ft_calloc(1, 1);
	while (buffer)
	{	
		free(buffer);
		buffer = get_next_line(fd_temp);
		if (!buffer)
			break ;
		buffer = remove_newline_from_buffer(buffer);
		if (is_matching_file(buffer, shell))
		{
			new_wildcard_tok(shell->user_command, buffer);
			temp = shell->user_command->start;
			while (temp)
			{
				printf("list elements: %s\n", temp->var);
				temp = temp->next;
			}
		}
	}
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
		while (!ft_strncmp(shell->wild_middle[j], buffer + i, ft_strlen(shell->wild_middle[j])))
			i++;
		i += ft_strlen(shell->wild_middle[j]);
		j++;
	}
	return (true);
}
/* before, ncmp sur la len de before
 * middle chr a partir de len de before + 1, depasse l'* et marche si pas de befor
 * after index a len de buffer - len de after puis ncmp sur la len de after
 * un seul passage et ajoute directement a user_command
 */

int	compare_after_wildcard(char *buffer, t_shell *shell)
{
	int	i;

	i = ft_strlen(buffer) - ft_strlen(shell->wild_after);
	if (buffer + i && ft_strncmp(buffer + i, shell->wild_after, ft_strlen(shell->wild_after)) == 0)
		return (true);
	return (false);
}
