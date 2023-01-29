/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:04:14 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/29 15:42:29 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	jump_text(char *line, int i)
{
	char	quote;

	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	return (i);
}

int	firstparsing(t_toklst *tokenlst, char *line, int start, int i)
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
	while (line[i] == '>')
		i++;
	if (start != i)
		new_back_tok(tokenlst, line, start, i);
	i = jump_wspace(line, i);
	return (i);
}

int	secondparsing(t_toklst *tokenlst, char *line, int start, int i)
{
	int		tmp;

	while (line[i] && !is_wspace(line[i]) && !is_sep(line[i]))
	{
		tmp = i;
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (checknextquote(line, line[i], tmp))
				i = jump_text(line, i);
			else
				return (errorintoken(tokenlst));
			i++;
		}
		else
			while (line[i] && !is_wspace(line[i]) && !is_sep(line[i])
				&& line[i] != '\'' && line[i] != '\"')
				i++;
	}
	if (start != i)
		new_back_tok(tokenlst, line, start, i);
	return (i);
}

void	parsing(t_toklst *tokenlst, char *line)
{
	int	start;
	int	i;

	i = 0;
	start = i;
	while (line[i])
	{
		i = firstparsing(tokenlst, line, start, i);
		start = i;
		i = secondparsing(tokenlst, line, start, i);
		if (i == -1)
			return ;
		start = i;
	}
}
