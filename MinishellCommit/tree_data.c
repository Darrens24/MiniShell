/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:32:25 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/21 16:49:11 by eleleux          ###   ########.fr       */
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

int	get_number_of_op(t_toklst *user_command, t_shell *shell)
{
	t_tok	*temp;
	int		parentheses;

	temp = user_command->start;
	shell->nb_of_op = 0;
	parentheses = 0;
	while (temp)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
		{
			parentheses = number_of_parentheses(temp);
			while (temp && parentheses > 0)
			{
				if (temp && ft_strncmp(temp->var, ")", 2) == 0)
					parentheses--;
				temp = temp->next;
			}
			if (!temp)
				break ;
		}
		if (temp && is_and_or(temp->var))
			shell->nb_of_op++;
		temp = temp->next;
	}
	return (shell->nb_of_op);
}

int	tree_number_of_pipes(t_toklst *user_command, t_shell *shell, char mode)
{
	t_tok	*temp;

	temp = go_to_branch_start(user_command);
	if (mode == 'l')
	{
		while (temp)
		{
			temp = pipe_reverse_jump_parentheses(temp);
			if (temp && ft_strncmp(temp->var, "|", 2) == 0)
				shell->l_nb_of_pipes++;
			if (temp && temp->prev)
				temp = temp->prev;
		}
	}
	else if (mode == 'r')
	{
		while (temp)
		{
			temp = pipe_jump_parentheses(temp);
			if (temp && ft_strncmp(temp->var, "|", 2) == 0)
				shell->r_nb_of_pipes++;
			if (temp && temp->next)
				temp = temp->next;
		}
	}
	return (EXIT_SUCCESS);
}
