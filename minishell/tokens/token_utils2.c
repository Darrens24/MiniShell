/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:29:05 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/11 15:15:40 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_command(t_shell *shell, int index)
{
	t_tok	*tmp;
	int		i;

	i = 0;
	tmp = shell->user_command->start;
	while (i++ < index && tmp)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->var);
}
