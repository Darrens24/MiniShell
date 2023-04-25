/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:08:59 by eleleux           #+#    #+#             */
/*   Updated: 2023/03/11 18:45:49 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_nb_of_wildcard(char *var)
{
	int	nb_of_wildcard;
	int	i;

	nb_of_wildcard = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == '*' && var[i + 1] == '*')
		{
			printf("Wildcard only manage current directory\n");
			return (-1);
		}
		else if (var[i] == '*')
			nb_of_wildcard++;
		i++;
	}
	return (nb_of_wildcard);
}

int	string_is_wildcard(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '*')
			return (TRUE);
	return (FALSE);
}

int	no_wildcard_before(char *str, int index)
{
	while (str && str[index])
	{
		if (str[index] == '*')
			return (FALSE);
		index--;
	}
	return (TRUE);
}

int	cmd_has_wildcard(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp)
	{
		if (string_is_wildcard(temp->var))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

int	free_wildcards(t_shell *shell)
{
	if (shell->wild_before)
		free(shell->wild_before);
	if (shell->wild_after)
		free(shell->wild_after);
	if (shell->wild_middle)
		free_array(shell->wild_middle);
	return (EXIT_SUCCESS);
}
