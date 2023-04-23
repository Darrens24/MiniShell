/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:08:04 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/18 18:46:54 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*squoteparser(t_tok *token, int i, char *newvar)
{
	int		start;
	char	*temp;

	i++;
	start = i;
	while (token->var[i] && token->var[i] != '\'')
			i++;
	temp = ft_strndup(token->var, start, i);
	newvar = join_without_leaks(newvar, temp);
	return (newvar);
}

int	squotejumper(t_tok *token, int i)
{
	i++;
	while (token->var[i] && token->var[i] != '\'')
			i++;
	i++;
	return (i);
}

char	*join_without_leaks(char *newvar, char *temp)
{
	char	*recipe;

	recipe = ft_strjoin(newvar, temp);
	free(newvar);
	free(temp);
	return (recipe);
}
