/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:32:25 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/24 18:23:22 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_and_or(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0)
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0
		|| ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

int	and_or_in_cmd_outside_parentheses(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
			temp = and_or_jump_parentheses(temp);
		if (temp && is_and_or(temp->var))
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
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
			temp = pipe_jump_parentheses(temp);
		if (temp && ft_strncmp(temp->var, "|", 2) == 0)
			return (1);
		else if (temp && temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (0);
}

int	and_or_in_cmd(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (is_and_or(temp->var))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	operator_in_cmd(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (is_operator(temp->var))
			return (1);
		temp = temp->next;
	}
	return (0);
}