/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:07:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/18 18:46:54 by pfaria-d         ###   ########.fr       */
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
				while (token->var[i]
					&& (ft_isalpha(token->var[i]) || token->var[i] == '_'))
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i - 1),
						newvar, env);
				i++;
			}
			else if (token->var[i] == '?')
			{
				newvar = join_without_leaks(newvar, ft_itoa(g_err));
				i++;
			}
			else if (!token->var[i] || is_wspace(token->var[i])
				|| token->var[i] == '"')
				newvar = join_without_leaks(newvar, "$");
			else
			{
				start = i;
				while (token->var[i]
					&& (ft_isalpha(token->var[i]) || token->var[i] == '_'))
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i),
						newvar, env);
			}
		}
		else
			newvar = join_without_leaks(newvar,
					ft_strndup(token->var, start, ++i));
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
				while (token->var[i]
					&& (ft_isalpha(token->var[i]) || token->var[i] == '_'))
					i++;
				if (token->var[i] && token->var[i] == '\"')
					return (-1);
				i++;
			}
			else if (token->var[i] == '?')
				i++;
			else if (!token->var[i] || is_wspace(token->var[i])
				|| token->var[i] == '"')
				i = i - 0;
			else
			{
				while (token->var[i]
					&& (ft_isalpha(token->var[i]) || token->var[i] == '_'))
					i++;
			}
		}
		else
			++i;
	}
	i++;
	return (i);
}
