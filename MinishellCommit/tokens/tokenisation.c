/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:47:01 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/12 16:49:40 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//modification du ++i dans jointok

void	dollarcase(t_tokation *tk, t_chained *env)
{
	tk->i++;
	if (tk->elem->var[tk->i] == '?' && !tk->elem->var[tk->i + 1])
	{
		tk->temp = ft_itoa(g_err);
		tk->newvar = ft_strjoin(tk->newvar, tk->temp);
		free(tk->temp);
		tk->i++;
	}
	else
	{
		tk->newvar = envvarparser(tk->elem, tk->i, tk->newvar, env);
		tk->i = envvarjumper(tk->elem, tk->i);
	}
}

void	norm_errors(t_tokation *tk, t_toklst *tokenlst)
{
	if (ft_strlen(tk->newvar) > 0)
		free(tk->newvar);
	if (tk->i == -2)
		errorintoken(tokenlst, "Error: no such user");
	else
		errorintoken(tokenlst, "No ending bracket");
}

void	antislash_norm(t_tokation *tk, t_chained *env)
{
	if (tk->elem->var[tk->i] == '\"')
	{
		tk->newvar = dquoteparser(tk->elem, ++tk->i, tk->newvar, env);
		tk->i = dquotejumper(tk->elem, tk->i);
	}
	else if (tk->elem->var[tk->i] == '\'')
	{
		tk->newvar = squoteparser(tk->elem, tk->i, tk->newvar);
		tk->i = squotejumper(tk->elem, tk->i);
	}
}

void	tilde_and_classicnorm(t_tokation *tk, t_chained *env)
{
	if (tk->elem->var && tk->elem->var[tk->i] == '~')
	{
		tk->i++;
		tk->newvar = vagueparser(tk->i, tk->newvar, env);
	}
	else if (tk->elem->var && tk->elem->var[tk->i])
	{
		tk->temp = ft_strndup(tk->elem->var, tk->start, ++tk->i);
		tk->newvar = ft_strjointok(tk->newvar, tk->temp);
	}
}

int	tokenisation(t_toklst *tokenlst, t_chained *env)
{
	t_tokation	*tk;

	tk = malloc(sizeof(t_tokation));
	tk->elem = tokenlst->start;
	while (tk->elem)
	{
		tk->i = 0;
		tk->newvar = NULL;
		while (tk->elem->var[tk->i])
		{
			token_norm_parsing(tk, env);
			if (tk->i == -1 || tk->i == -2)
				return (norm_errors(tk, tokenlst), -1);
		}
		free(tk->elem->var);
		tk->elem->var = tk->newvar;
		tk->elem = tk->elem->next;
	}
	return (free(tk), 0);
}
