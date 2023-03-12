/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:07:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/12 16:04:48 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

		/* BRACKET		start = ++i;
				while (token->var[i] && token->var[i] != '\"'
					&& token->var[i] != '}')
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i),
						newvar, env);
				i++;*/

		/* CLASSIC		start = i;
				while (token->var[i] && token->var[i] != '\"'
					&& token->var[i] != '\'')
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i),
						newvar, env);*/

		/* DQUOTE	while (token->var[i] && token->var[i] != '\"'
					&& token->var[i] != '\'')
					i++;*/

static int	bracket_case(t_tok *token, int i, char *newvar, t_chained *env)
{
	int		start;
	char	*temp;

	start = i + 1;
	while (token->var[i] && token->var[i] != '\"'
		&& token->var[i] != '}')
		i++;
	temp = ft_strndup(token->var, start, i);
	newvar = envfinder(temp, newvar, env);
	free(temp);
	i++;
	return (i);
}

static char	*classic_case(t_tok *token, int *i, char *newvar, t_chained *env)
{
	int		start;
	char	*temp;

	start = *i;
	while (token->var[*i] && token->var[*i] != '\"'
		&& token->var[*i] != '\'')
		*i += 1;
	temp = ft_strndup(token->var, start, *i);
	newvar = envfinder(temp, newvar, env);
	free(temp);
	return (newvar);
}

char	*dquoteparser(t_tok *token, int i, char *newvar, t_chained *env)
{
	int		start;
	char	*temp;

	while (token->var[i] && token->var[i] != '\"')
	{
		start = i;
		if (token->var[i] && token->var[i] == '$')
		{
			i++;
			if (token->var[i] && token->var[i] == '{')
				i += bracket_case(token, i, newvar, env);
			else if (!token->var[i] || is_wspace(token->var[i])
				|| token->var[i] == '"')
				newvar = join_without_leaks(newvar, "$");
			else
				newvar = classic_case(token, &i, newvar, env);
		}
		else
		{
			i++;
			temp = ft_strndup(token->var, start, i);
			newvar = join_without_leaks(newvar, temp);
		}
	}
	return (newvar);
}

static int	norm_dquotejumper(t_tok *token, int i)
{
	while (token->var[i] && token->var[i] != '\"'
		&& token->var[i] != '\'')
		i++;
	return (i);
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
				i += norm_dquotejumper(token, i);
		}
		else
			++i;
	}
	return (i + 1);
}
