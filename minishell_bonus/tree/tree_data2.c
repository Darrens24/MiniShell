/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:24:42 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 13:16:57 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	and_or_in_cmd_outside_parentheses(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0 && temp->quote == 0)
			temp = and_or_jump_parentheses(temp);
		if (temp && is_and_or(temp->var) && temp->quote == 0)
			return (1);
		else if (temp && temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (0);
}

int	pipe_in_cmd_outside_parentheses(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0 && temp->quote == 0)
			temp = pipe_jump_parentheses(temp);
		if (temp && ft_strncmp(temp->var, "|", 2) == 0 && temp->quote == 0)
			return (1);
		else if (temp && temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (0);
}

int	parenthese_in_command(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (ft_strncmp(temp->var, "(", 2) == 0)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}
