/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:07:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/24 11:07:09 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	varjumper(char *var, int i)
{
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	return (i);
}

char	*dquotep2(t_tok *token, int *y, char *newvar, t_chained *env)
{
	int	start;
	int	i;

	i = *y;
	start = i;
	if (token->var[i] && token->var[i] == '{' && i++ > -1)
	{
		i = varjumper(token->var, start = i);
		newvar = envfinder(ft_strndup(token->var, start, i++),
				newvar, env);
	}
	else if (token->var[i] == '?' && i++ > -1)
		newvar = join_without_leaks(newvar, ft_itoa(g_err));
	else if (!token->var[i] || is_wspace(token->var[i])
		|| token->var[i] == '"' || !(ft_isalnum(token->var[i])
			|| token->var[i] == '_'))
		newvar = join_without_leaks2(newvar, "$");
	else
	{
		i = varjumper(token->var, start = i);
		newvar = envfinder(ft_strndup(token->var, start, i),
				newvar, env);
	}
	*y = i;
	return (newvar);
}

char	*dquoteparser(t_tok *token, int i, char *newvar, t_chained *env)
{
	int	start;

	while (token->var[i] && token->var[i] != '\"')
	{
		start = i;
		if (token->var[i] && token->var[i] == '$' && i++ > -1)
		{
			newvar = dquotep2(token, &i, newvar, env);
		}
		else
			newvar = join_without_leaks(newvar,
					ft_strndup(token->var, start, ++i));
	}
	return (newvar);
}

int	dquotej2(t_tok *token, int i)
{
	i++;
	if (token->var[i] && token->var[i] == '{')
	{
		while (token->var[i]
			&& (ft_isalnum(token->var[i]) || token->var[i] == '_'))
			i++;
		if (token->var[i] && token->var[i] == '\"')
			return (-1);
		i++;
	}
	else if (token->var[i] == '?')
		i++;
	else if (!token->var[i] || is_wspace(token->var[i])
		|| token->var[i] == '"' || !(ft_isalnum(token->var[i])
			&& token->var[i] == '_'))
		i = i - 0;
	else
	{
		while (token->var[i]
			&& (ft_isalnum(token->var[i]) || token->var[i] == '_'))
			i++;
	}
	return (i);
}

int	dquotejumper(t_tok *token, int i)
{
	while (token->var[i] && token->var[i] != '\"')
	{
		if (token->var[i] && token->var[i] == '$')
			i = dquotej2(token, i);
		else
			++i;
	}
	i++;
	return (i);
}
