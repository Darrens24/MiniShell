/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:11:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/14 17:40:01 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_is_wildcard(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '*')
			return (true);
	return (false);
}

int	cmd_has_wildcard(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp)
	{
		if (string_is_wildcard(temp->var))
			return (true);
		temp = temp->next;
	}
	return (false);
}

int	jump_next_wildcard(char *str, int index)
{
	while (str[index] && str[index] != '*')
		index++;
	//index--;
	return (index);
}

int	jump_previous_wildcard(char *str, int index)
{
	while (str[index] && str[index] != '*')
		index--;
	index++;
	return (index);
}

int	parse_wildcard(t_shell *shell, char **envp)
{
	int		i;
	t_tok	*temp;
	int		nb_of_wildcards;

	temp = shell->user_command->start;
	nb_of_wildcards = 0;
	while (temp && !string_is_wildcard(temp->var))
		temp = temp->next;
	nb_of_wildcards = 0;
	i = 0;
	while (temp->var[i])
	{
		if (temp->var[i] == '*')
			nb_of_wildcards++;
		i++;
	}
	i = 0;
	if (nb_of_wildcards == 1)
	{
		while (temp->var[i])
		{
			if (temp->var[i] == '*' && temp->var[i + 1])
				shell->wild_after = ft_strndup(temp->var, i + 1, jump_next_wildcard(temp->var, i + 1));
			if (temp->var[i] == '*' && temp->var[i - 1])
				shell->wild_before = ft_strndup(temp->var, jump_previous_wildcard(temp->var, i - 1), i);  
			i++;
		}
		printf("shell->wild_before : %s\n", shell->wild_before);
		printf("shell->wild_after : %s\n", shell->wild_after);
		execute_ls_in_tmp(shell, envp);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
