/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:04:14 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/28 14:06:40 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_wspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	jump_wspace(char *line, int i)
{
	while (line[i] && is_wspace(line[i]))
		i++;
	return (i);
}

static int	checknextquote(char *line, char quote)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

void	parsing(t_toklst *tokenlst, char *line)
{
	int	start;
	int	i;

	i = 0;
	while (line[i])
	{
		i = jump_wspace(line, i);
		start = i;
		while (line[i] == '|')
			i++;
		if (start != i)
			new_back_tok(tokenlst, line, start, i);
		i = jump_wspace(line, i);
		start = i;
		while (line[i] == '<')
			i++;
		if (start != i)
			new_back_tok(tokenlst, line, start, i);
		i = jump_wspace(line, i);
		while (line [i] && !is_wspace(line[i]))
			i++;
		if (start != i)
			new_back_tok(tokenlst, line, start, i);
	}
}
