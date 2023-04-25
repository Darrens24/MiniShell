/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:11:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/18 18:46:54 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_wildcard(t_shell *shell, char **envp)
{
	t_tok	*temp;
	int		nb_of_wildcard;
	int		i;

	temp = shell->user_command->start;
	while (temp && !string_is_wildcard(temp->var))
		temp = temp->next;
	nb_of_wildcard = get_nb_of_wildcard(temp->var);
	if (nb_of_wildcard < 0)
		return (EXIT_FAILURE);
	shell->wild_middle = malloc(sizeof(char *) * (nb_of_wildcard));
	if (!shell->wild_middle)
		return (EXIT_FAILURE);
	i = -1;
	while (shell->wild_middle[++i])
		shell->wild_middle[i] = NULL;
	get_asked_wildcards(temp->var, shell);
	execute_ls_in_tmp(shell, envp);
	get_wildcard_files(shell);
	return (EXIT_SUCCESS);
}

int	one_wildcard_only(char *buffer, t_shell *shell)
{
	if (shell->wild_middle[0])
	{
		if (compare_middle_wildcard(buffer, shell) == TRUE)
			return (TRUE);
	}
	else if (shell->wild_before)
	{
		if (ft_strncmp(buffer, shell->wild_before,
				ft_strlen(shell->wild_before)) == 0)
			return (TRUE);
	}
	else if (shell->wild_after)
	{
		if (compare_after_wildcard(buffer, shell) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

int	two_wildcards(char *buffer, t_shell *shell)
{
	if (shell->wild_before && shell->wild_middle[0])
	{
		if (ft_strncmp(buffer, shell->wild_before,
				ft_strlen(shell->wild_before)) == 0
			&& compare_middle_wildcard(buffer, shell))
			return (TRUE);
	}
	else if (shell->wild_before && shell->wild_after)
	{
		if (ft_strncmp(buffer, shell->wild_before,
				ft_strlen(shell->wild_before)) == 0
			&& compare_after_wildcard(buffer, shell) == TRUE)
			return (TRUE);
	}
	else if (shell->wild_middle[0] && shell->wild_after)
	{
		if (compare_middle_wildcard(buffer, shell)
			&& compare_after_wildcard(buffer, shell))
			return (TRUE);
	}
	return (FALSE);
}

int	all_wildcards(char *buffer, t_shell *shell)
{
	if (shell->wild_before && shell->wild_middle && shell->wild_after)
	{
		if (ft_strncmp(buffer, shell->wild_before,
				ft_strlen(shell->wild_before)) == 0
			&& compare_after_wildcard(buffer, shell)
			&& compare_middle_wildcard(buffer, shell))
			return (TRUE);
	}
	return (FALSE);
}

int	is_matching_file(char *buffer, t_shell *shell)
{
	if (shell->wild_before && shell->wild_middle && shell->wild_after)
		return (all_wildcards(buffer, shell));
	else if ((shell->wild_before && shell->wild_middle[0])
		|| (shell->wild_before && shell->wild_after)
		|| (shell->wild_middle[0] && shell->wild_after))
		return (two_wildcards(buffer, shell));
	else if (shell->wild_middle[0]
		|| shell->wild_before
		|| shell->wild_after)
		return (one_wildcard_only(buffer, shell));
	return (FALSE);
}
