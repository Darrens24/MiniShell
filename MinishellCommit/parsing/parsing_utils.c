/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:37:28 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/27 10:31:44 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_wspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_sep(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

int	jump_wspace(char *line, int i)
{
	while (line[i] && is_wspace(line[i]))
		i++;
	return (i);
}

int	checknextquote(char *line, char quote, int start)
{
	int	i;

	i = start + 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

int	errorintoken(t_toklst *tokenlst, char *error)
{
	printf("%s\n", error);
	clear_toklst(tokenlst);
	return (-1);
}
