/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:29:05 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/09 09:04:00 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_emptytok(t_toklst *list)
{
	if (list->nb_elem == 0)
		return (1);
	return (0);
}

void	print_toklst(t_toklst *list)
{
	t_tok	*temp;

	temp = list->start;
	while (temp)
	{
		printf("%s\n", temp->var);
		temp = temp->next;
	}
}

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

char	*get_b_command(t_shell *shell, int index, char **command)
{
	int		i;

	(void) shell;
	i = 0;
	while (i < index)
		i++;
	if (!command[i])
		return (NULL);
	return (command[i]);
}
