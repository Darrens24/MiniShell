/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:02:41 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 15:05:51 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_norm_parsing(t_tokation *tk, t_chained *env)
{
	tk->start = tk->i;
	if (tk->elem->var[tk->i] == '\"' || tk->elem->var[tk->i] == '\'')
		antislash_norm(tk, env);
	else if ((tk->elem->var[tk->i] == '$' && !tk->elem->prev)
		|| (tk->elem->var[tk->i] == '$' && tk->elem->prev
			&& !(ft_strncmp(tk->elem->prev->var, "<<", 3) == 0
				&& tk->elem->prev->quote == 0)))
		dollarcase(tk, env);
	else if ((tk->elem->var && tk->elem->var[tk->i] == '~')
		|| (tk->elem->var && tk->elem->var[tk->i]))
		tilde_and_classicnorm(tk, env);
}

char	*vagueparser(int i, char *newvar, t_chained	*envp)
{
	char	*vague;

	if (i != 1)
	{
		vague = ft_strdup("~");
		return (newvar = join_without_leaks(newvar, vague));
	}
	newvar = envfinder("HOME", newvar, envp);
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
		while (token->var[i] && token->var[i] != '\'' && token->var[i] != '\"'
			&& (ft_isalnum(token->var[i]) || token->var[i] == '_'))
			i++;
	}
	return (i);
}

char	*envfinder(char *line, char *newvar, t_chained *env)
{
	t_node	*elem;
	int		len;
	char	*temp;

	temp = line;
	line = ft_strjoin(temp, "=");
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	elem = env->end;
	len = ft_strlen(line);
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
		{
			temp = ft_strndup(elem->variable, len, ft_strlen(elem->variable));
			newvar = join_without_leaks(newvar, temp);
		}
		elem = elem->prev;
	}
	free(line);
	return (newvar);
}

char	*envvarparser(t_tok *token, int i, char *newvar, t_chained *env)
{
	int		start;
	char	*temp;

	start = i;
	temp = NULL;
	if (token->var[i] && token->var[i] == '{' && i++ > -1)
	{
		while (token->var[i] && token->var[i] != '}')
			i++;
		temp = ft_strndup(token->var, start, i++);
		newvar = envfinder(temp, newvar, env);
	}
	else if (!token->var[i] || is_wspace(token->var[i])
		|| token->var[i] == '\"' || token->var[i] == '\'')
		newvar = ft_strjoin(newvar, "$");
	else
	{
		while (token->var[i] && token->var[i] != '\'' && token->var[i] != '\"'
			&& (ft_isalnum(token->var[i]) || token->var[i] == '_'))
			i++;
		temp = ft_strndup(token->var, start, i);
		newvar = envfinder(temp, newvar, env);
	}
	return (newvar);
}
