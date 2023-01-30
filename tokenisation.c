/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:47:01 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/30 14:08:22 by pfaria-d         ###   ########.fr       */
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

int	envjumper(char *line, char *newvar, t_chained *env)
{
	t_node	*elem;
	int	len;
	int	tmp;

	line = ft_strjoin(line, "=");
	elem = env->end;
	tmp = ft_strlen(newvar);
	len = ft_strlen(line);
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
			newvar = ft_strjoin(newvar, ft_strndup(line, len, ft_strlen(elem->variable)));
		elem = elem->prev;
	}
	return ((ft_strlen(newvar) - tmp) + 1);
}

char	*quoteparser(t_tok *token, int i, char *newvar, t_chained *env)
{
	int	start;

	i++;
	while (token->var[i] && token->var[i] != '\"')
	{
		start = i;
		if (token->var[i] == '$')
		{
			i++;
			if (token->var[i] == '{')
			{
				start = ++i;
				while (token->var[i] && token->var[i] != '\"' && token->var[i] != '}')
					i++;
				newvar = envfinder(ft_strndup(token->var, start, i), newvar, env);
				i += envjumper(token->var, newvar, env);
			}
		}
		else
			newvar = ft_strjoin(newvar, ft_strndup(token->var, start, ++i));
	}
	i++;
	return (newvar); 
}

int	quotejumper(t_tok *token, int i, char *newvar, t_chained *env)
{
	int	start;

	i++;
	while (token->var[i] && token->var[i] != '\"')
	{
		start = i;
		if (token->var[i] == '$')
		{
			i++;
			if (token->var[i] == '{')
			{
				while (token->var[i] && token->var[i] != '\"' && token->var[i] != '}')
					i++;
				if (token->var[i] && token->var[i] == '\"')
					return (-1);
				newvar = envfinder(ft_strndup(token->var, start, i), newvar, env);
				i += envjumper(token->var, newvar, env);
			}
		}
		else
			newvar = ft_strjoin(newvar, ft_strndup(token->var, start, ++i));
	}
	i++;
	return (i); 
}

void	tokenisation(t_toklst *tokenlst, t_chained *env)
{
	t_tok   *elem;
	int		i;
	char	*newvar;
	int		start;

    elem = malloc(sizeof(*elem));
	elem = tokenlst->start;
	newvar = 0;
	while(elem)
	{
		i = 0;
		while(elem->var[i])
		{
			start = i;
			if (elem->var[i] == '\"')
			{
				newvar = quoteparser(elem, i, newvar, env);
				i = quotejumper(elem, i, newvar, env);
			}
			//else if (elem->var[i] == '\'')
			//	i = 1quoteparser(elem, i, newvar);
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
		newvar = 0;
	}
}
