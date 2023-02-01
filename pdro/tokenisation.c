/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:47:01 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/01 14:25:10 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envfinder(char *line, char *newvar, t_chained *env)
{
	t_node	*elem;
	int	len;

	line = ft_strjoin(line, "=");
	elem = env->end;
	len = ft_strlen(line);
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
			newvar = ft_strjoin(newvar, ft_strndup(elem->variable, len, ft_strlen(elem->variable)));
		elem = elem->prev;
	}
	return (newvar);
}

char    *envvarparser(t_tok *token, int i, char *newvar, t_chained *env)
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
	else if (!token->var[i] || is_wspace(token->var[i]) || token->var[i] == '\"' || token->var[i] == '\'')
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

int    envvarjumper(t_tok *token, int i)
{
	if (token->var[i] && token->var[i] == '{')
	{
		i++;
		while (token->var[i] && token->var[i] != '}')
			i++;
		i++;
	}
	else if (!token->var[i] || is_wspace(token->var[i]) || token->var[i] == '\"' || token->var[i] == '\'')
		i = i;
	else
	{
		while (token->var[i] && token->var[i] != '\'' && token->var[i] != '\"')
			i++;
	}
	return (i);
}
char	*dquoteparser(t_tok *token, int i, char *newvar, t_chained *env)
{
	int	start;

	i++;
	while (token->var[i] && token->var[i] != '\"')
	{
		start = i;
		if (token->var[i] && token->var[i] == '$')
		{
			i++;
			if (token->var[i] &&token->var[i] == '{')
			{
				start = ++i;
				while (token->var[i] && token->var[i] != '\"' && token->var[i] != '}')
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i), newvar, env);
				i++;
			}
			else if (!token->var[i] || is_wspace(token->var[i]) || token->var[i] == '"')
				newvar = ft_strjoin(newvar, "$");
			else
			{
				start = i;
				while (token->var[i] && token->var[i] != '\"' && token->var[i] != '\'')
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i), newvar, env);
			}
		}
		else
			newvar = ft_strjoin(newvar, ft_strndup(token->var, start, ++i));
	}
	i++;
	return (newvar); 
}

int	dquotejumper(t_tok *token, int i, char *newvar, t_chained *env)
{
	int	start;

	i++;
	while (token->var[i] && token->var[i] != '\"')
	{
		start = i;
		if (token->var[i] && token->var[i] == '$')
		{
			i++;
			if (token->var[i] && token->var[i] == '{')
			{
				while (token->var[i] && token->var[i] != '\"' && token->var[i] != '}')
					i++;
				if (token->var[i] && token->var[i] == '\"')
					return (-1);
				newvar = envfinder(ft_strndup(token->var, start, i), newvar, env);
				i++;
			}
			else if (!token->var[i] || is_wspace(token->var[i]) || token->var[i] == '"')
				newvar = ft_strjoin(newvar, "$");
			else
			{
				while (token->var[i] && token->var[i] != '\"' && token->var[i] != '\"')
					i++;
			}
		}
		else
			++i;
	}
	i++;
	return (i); 
}

char    *squoteparser(t_tok *token, int i, char *newvar)
{
	int     start;

	i++;
	start = i;
	while (token->var[i] && token->var[i] != '\'')
			i++;
	newvar = ft_strjoin(newvar, ft_strndup(token->var, start, i));
	return (newvar);
}

int     squotejumper(t_tok *token, int i)
{
	i++;
	while (token->var[i] && token->var[i] != '\'')
			i++;
	return (i);
}

void    tokenisation(t_toklst *tokenlst, t_chained *env)
{
	t_tok   *elem;
	int             i;
	char    *newvar;
	int             start;

	elem = malloc(sizeof(*elem));
        elem = tokenlst->start;
        while(elem)
        {
                newvar = 0;
                i = 0;
                while(elem->var[i])
                {
                        start = i;
                        if (elem->var[i] == '\"')
                        {
                                newvar = dquoteparser(elem, i, newvar, env);
                                i = dquotejumper(elem, i, newvar, env);
                        }
                        else if (elem->var[i] == '\'')
                        {
                                newvar = squoteparser(elem, i, newvar);
                                i = squotejumper(elem, i);
                        }
                        else if (elem->var[i] == '$')
                        {
							i++;
							newvar = envvarparser(elem, i, newvar, env);
							i = envvarjumper(elem, i);
                        }
                        else
                                newvar = ft_strjoin(newvar, ft_strndup(elem->var, start, ++i));
                        if (i == -1)
                        {
                                if (ft_strlen(newvar) > 0)
                                        free(newvar);
                                errorintoken(tokenlst, "no ending bracket");
                                return ;
                        }
                }
                elem->var = newvar;
                elem = elem->next;
        }
        newvar = 0;
}
