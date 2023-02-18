/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:11:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/18 16:51:19 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_wildcard(t_shell *shell, char **envp)
{
	t_tok	*temp;
	int 	nb_of_wildcard;

	temp = shell->user_command->start;
	while (temp && !string_is_wildcard(temp->var))
		temp = temp->next;
	nb_of_wildcard = get_nb_of_wildcard(temp->var);
	if (nb_of_wildcard < 0)
		return (EXIT_FAILURE);
	shell->wild_middle = malloc(sizeof(char *) * (nb_of_wildcard));
	if (!shell->wild_middle)
		return (EXIT_FAILURE);
	get_asked_wildcards(temp->var, shell);
	execute_ls_in_tmp(shell, envp);
	get_wildcard_files(shell);
	return (EXIT_SUCCESS);
}
/*
int	one_wildcard_only(char *buffer, t_shell *shell)
{
}

int	two_wildcards(char *buffer, t_shell *shell)
{
}

int	all_wildcards(char *buffer, t_shell *shell)
{
}
*/
int	is_matching_file(char *buffer, t_shell *shell)
{
	if (shell->wild_before && shell->wild_middle && shell->wild_after)
	{
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0 && compare_after_wildcard(buffer, shell) && compare_middle_wildcard(buffer, shell))
			return (true);
	}
	else if (shell->wild_before && shell->wild_middle[0])
	{
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0 && compare_middle_wildcard(buffer, shell))
			return (true);
	}
	else if (shell->wild_before && shell->wild_after)
	{
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0 && compare_after_wildcard(buffer, shell) == true)
			return (true);
	}
	else if (shell->wild_middle[0] && shell->wild_after)
	{
		if (compare_middle_wildcard(buffer, shell) && compare_after_wildcard(buffer, shell))
			return (true);
	}
	else if (shell->wild_middle[0])
	{
		if (compare_middle_wildcard(buffer, shell) == true)
			return (true);
	}
	else if (shell->wild_before)
	{
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0)
			return (true);
	}
	else if (shell->wild_after)
	{
		if (compare_after_wildcard(buffer, shell) == true)
			return (true);
	}
	return (false);
}

