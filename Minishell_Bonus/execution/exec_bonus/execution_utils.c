/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:49:26 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/27 16:49:48 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_or(char *cmd)
{
	if (ft_strncmp(cmd, "||", 3) == 0)
		return (1);
	return (0);
}

int	is_and(char *cmd)
{
	if (ft_strncmp(cmd, "&&", 3) == 0)
		return (1);
	return (0);
}

int	is_pipe(char *cmd)
{
	if (ft_strncmp(cmd, "|", 2) == 0)
		return (1);
	return (0);
}
