/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:04:14 by pfaria-d          #+#    #+#             */
/*   Updated: 2022/12/22 12:58:15 by pfaria-d         ###   ########.fr       */
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

static int	checknextquote(char *line, char quote, int start)
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

void	parsing(t_toklst *tokenlst, char *line)
{
	int	start;
	int	i;
	char	quote;
	int	tmp;

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
		start = i;
		while (line[i] && !is_wspace(line[i]) && line[i] != '|' && line[i] != '<')
		{
			tmp = i;
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (checknextquote(line, line[i], tmp))
			{
				quote = line[i++];
				while (line[i] && line[i] != quote)
					i++;
			}
			else
			{
				printf("no ending quote\n");
				clear_toklst(tokenlst);
				return ;
			}
			i++;
		}
		else
			while (line[i] && !is_wspace(line[i])
				&& line[i] != '|' && line[i] != '<' && line[i] != '\'' && line[i] != '\"')
				i++;
		}
		if (start != i)
			new_back_tok(tokenlst, line, start, i);
	}
}
