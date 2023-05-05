/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:11:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/03 13:00:39 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_wildcard(t_shell *shell, char **envp, t_tok *temp)
{
	int		nb_of_wildcard;
	t_tok	*map;

	nb_of_wildcard = get_nb_of_wildcard(temp->var);
	if (nb_of_wildcard < 0)
		return (EXIT_FAILURE);
	else if (nb_of_wildcard == 0 && temp->next && cmd_has_wildcard(temp->next))
		return (parse_wildcard(shell, envp, temp->next));
	shell->wild_middle = malloc(sizeof(char *) * (nb_of_wildcard + 1));
	if (!shell->wild_middle)
		return (EXIT_FAILURE);
	shell->wild_before = NULL;
	shell->wild_after = NULL;
	shell->wild_all = 0;
	get_asked_wildcards(temp->var, shell);
	execute_ls_in_tmp(shell, envp);
	map = temp->next;
	get_wildcard_files(shell, temp);
	if (map && cmd_has_wildcard(map))
		return (parse_wildcard(shell, envp, map));
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
	if (shell->wild_all == 1)
		return (TRUE);
	else if (shell->wild_before && shell->wild_middle && shell->wild_after)
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
