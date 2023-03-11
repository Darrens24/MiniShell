/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:47:01 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/11 16:12:52 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//modification du ++i dans jointok

char	*envfinder(char *line, char *newvar, t_chained *env)
{
	t_node	*elem;
	int		len;

	line = ft_strjoin(line, "=");
	elem = env->end;
	len = ft_strlen(line);
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
			newvar = ft_strjoin(newvar, ft_strndup(elem->variable, len,
						ft_strlen(elem->variable)));
		elem = elem->prev;
	}
	return (newvar);
}

char	*envvarparser(t_tok *token, int i, char *newvar, t_chained *env)
{
	int	start;

	if (token->var[i] && token->var[i] == '{')
	{
		start = ++i;
		while (token->var[i] && token->var[i] != '}')
			i++;
		newvar = envfinder(ft_strndup(token->var, start, i), newvar, env);
		i++;
	}
	else if (!token->var[i] || is_wspace(token->var[i])
		|| token->var[i] == '\"' || token->var[i] == '\'')
		newvar = ft_strjoin(newvar, "$");
	else
	{
		start = i;
		while (token->var[i] && token->var[i] != '\'' && token->var[i] != '\"')
			i++;
		newvar = envfinder(ft_strndup(token->var, start, i), newvar, env);
	}
	return (newvar);
}

int	envvarjumper(t_tok *token, int i)
{
	if (token->var[i] && token->var[i] == '{')
	{
		i++;
		while (token->var[i] && token->var[i] != '}')
			i++;
		i++;
	}
	else if (!token->var[i] || is_wspace(token->var[i])
		|| token->var[i] == '\"' || token->var[i] == '\'')
		i += 0;
	else
	{
		while (token->var[i] && token->var[i] != '\'' && token->var[i] != '\"')
			i++;
	}
	return (i);
}

char	*vagueparser(int i, char *newvar, t_chained	*envp)
{
	if (i != 1)
		return (newvar = ft_strjoin(newvar, "~"));
	newvar = envfinder("HOME", newvar, envp);
	return (newvar);
}
/*
static void	dollarcase(t_tok *elem, int *i, char *temp, char *newvar)
{
	*i += 1;
	if (elem->var[*i] == '?' && !elem->var[*i + 1])
	{
		temp = ft_itoa(g_err);
		newvar = ft_strjoin(newvar, temp);
		*i += 1;
	}
	else
	{
		newvar = envvarparser(elem, *i, newvar, env);
		*i = envvarjumper(elem, *i);
	}
}*/

void	tokenisation(t_toklst *tokenlst, t_chained *env)
{
	t_tokenisation	*tkion;
/*	t_tok	*elem;
	int		i;
	char	*newvar;
	int		start;
	char	*temp;*/

	tkion = malloc(sizeof(t_tokenisation));
	tkion->elem = tokenlst->start;
	while (tkion->elem)
	{
		tkion->newvar = 0;
		tkion->i = 0;
		while (tkion->elem->var[tkion->i])
		{
			tkion->start = tkion->i;
			if (tkion->elem->var[tkion->i] == '\"')
			{
				tkion->newvar = dquoteparser(tkion->elem, ++tkion->i, tkion->newvar, env);
				tkion->i = dquotejumper(tkion->elem, tkion->i);
			}
			else if (tkion->elem->var[tkion->i] == '\'')
			{
					tkion->newvar = squoteparser(tkion->elem, tkion->i, tkion->newvar);
					tkion->i = squotejumper(tkion->elem, tkion->i);
			}
			else if ((tkion->elem->var[tkion->i] == '$' && !tkion->elem->prev)
				|| (tkion->elem->var[tkion->i] == '$' && tkion->elem->prev
					&& !(ft_strncmp(tkion->elem->prev->var, "<<", 3) == 0
						&& tkion->elem->prev->quote == 0)))
			{
				tkion->i++;
				if (tkion->elem->var[tkion->i] == '?' && !tkion->elem->var[tkion->i + 1])
				{
					tkion->temp = ft_itoa(g_err);
					tkion->newvar = ft_strjoin(tkion->newvar, tkion->temp);
					tkion->i++;
				}
				else
				{
					tkion->newvar = envvarparser(tkion->elem, tkion->i, tkion->newvar, env);
					tkion->i = envvarjumper(tkion->elem, tkion->i);
				}
			}
			else if (tkion->elem->var && tkion->elem->var[tkion->i] == '~')
			{
				tkion->i++;
				tkion->newvar = vagueparser(tkion->i, tkion->newvar, env);
			}
			else if (tkion->elem->var && tkion->elem->var[tkion->i])
			{
				tkion->temp = ft_strndup(tkion->elem->var, tkion->start, ++tkion->i);
				tkion->newvar = ft_strjointok(tkion->newvar, tkion->temp);
			}
			if (tkion->i == -1 || tkion->i == -2)
			{
				if (ft_strlen(tkion->newvar) > 0)
					free(tkion->newvar);
				if (tkion->i == -2)
					errorintoken(tokenlst, "Error: no such user");
				else
					errorintoken(tokenlst, "No ending bracket");
				return ;
			}
		}
		free(tkion->elem->var);
		tkion->elem->var = tkion->newvar;
		tkion->elem = tkion->elem->next;
	}
	tkion->newvar = 0;
}
