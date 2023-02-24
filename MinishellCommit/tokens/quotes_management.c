/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:07:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/17 10:05:30 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dquoteparser(t_tok *token, int i, char *newvar, t_chained *env)
{
	int	start;

	while (token->var[i] && token->var[i] != '\"')
	{
		start = i;
		if (token->var[i] && token->var[i] == '$')
		{
			i++;
			if (token->var[i] && token->var[i] == '{')
			{
				start = ++i;
				while (token->var[i] && token->var[i] != '\"'
					&& token->var[i] != '}')
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i),
						newvar, env);
				i++;
			}
			else if (!token->var[i] || is_wspace(token->var[i])
				|| token->var[i] == '"')
				newvar = ft_strjoin(newvar, "$");
			else
			{
				start = i;
				while (token->var[i] && token->var[i] != '\"'
					&& token->var[i] != '\'')
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i),
						newvar, env);
			}
		}
		else
			newvar = ft_strjoin(newvar, ft_strndup(token->var, start, ++i));
	}
	i++;
	return (newvar);
}

int	dquotejumper(t_tok *token, int i)
{
	while (token->var[i] && token->var[i] != '\"')
	{
		if (token->var[i] && token->var[i] == '$')
		{
			i++;
			if (token->var[i] && token->var[i] == '{')
			{
				while (token->var[i] && token->var[i] != '\"'
					&& token->var[i] != '}')
					i++;
				if (token->var[i] && token->var[i] == '\"')
					return (-1);
				i++;
			}
			else if (!token->var[i] || is_wspace(token->var[i])
				|| token->var[i] == '"')
				i = i - 0;
			else
			{
				while (token->var[i] && token->var[i] != '\"'
					&& token->var[i] != '\'')
					i++;
			}
		}
		else
			++i;
	}
	i++;
	return (i);
}
