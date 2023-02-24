/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squotes_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:08:04 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/02/15 16:11:58 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*squoteparser(t_tok *token, int i, char *newvar)
{
	int	start;

	i++;
	start = i;
	while (token->var[i] && token->var[i] != '\'')
			i++;
	newvar = ft_strjoin(newvar, ft_strndup(token->var, start, i));
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
