/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:47:01 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/28 11:30:35 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjointok(char const *s1, char const *s2)
{
	char	*recipe;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	recipe = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!recipe)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		recipe[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		recipe[i++] = s2[j++];
	recipe[i] = '\0';
	free((void *)s1);
	free((void *)s2);
	return (recipe);
}

char	*envinder(char *line, char *newvar, t_chained *env)
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

int    envvarjumper(t_tok *token, int i)
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

void    tokenisation(t_toklst *tokenlst, t_chained *env)
{
	t_tok   *elem;
	int             i;
	char    *newvar = NULL;
	int             start;
	char	*temp = NULL;

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
						newvar = dquoteparser(elem, ++i, newvar, env);
						i = dquotejumper(elem, i);
					}
					else if (elem->var[i] == '\'')
					{
							newvar = squoteparser(elem, i, newvar);
							i = squotejumper(elem, i);
					}
					else if ((elem->var[i] == '$' && !elem->prev) || (elem->var[i] == '$' && elem->prev && !(ft_strncmp(elem->prev->var, "<<", 3) == 0 && elem->prev->quote == 0)))
					{
						i++;
						if (elem->var[i] == '?' && !elem->var[i + 1])
						{
							temp = ft_itoa(g_err);
							newvar = ft_strjoin(newvar, temp);
							i++;
						}
						else
						{
							newvar = envvarparser(elem, i, newvar, env);
							i = envvarjumper(elem, i);
						}
					}
					else if (elem->var && elem->var[i] == '~')
					{
						i++;
						newvar = vagueparser(i, newvar, env);
					}
					else if (elem->var && elem->var[i])
					{
						temp = ft_strndup(elem->var, start, ++i);
						newvar = ft_strjointok(newvar, temp);
					}
					if (i == -1 || i == -2)
					{
						if (ft_strlen(newvar) > 0)
								free(newvar);
						if (i == -2)
							errorintoken(tokenlst, "Error: no such user");
						else
							errorintoken(tokenlst, "no ending bracket");
						return ;
					}
				//printf("%s\n", elem->var[i]);
			}
			free(elem->var);
			elem->var = newvar;
			elem = elem->next;
	}
//	if (newvar)
//		free(newvar);
	newvar = 0;
}
