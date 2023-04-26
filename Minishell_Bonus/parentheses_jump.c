/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_jump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:10:39 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/26 11:18:34 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*pipe_jump_parentheses(t_tok *temp)
{
	int	parentheses;

	while (temp && ft_strncmp(temp->var, "|", 2) != 0)
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
		}
		else
			temp = temp->next;
	}
	return (temp);
}

t_tok	*and_or_jump_parentheses(t_tok *temp)
{
	int	parentheses;

	while (temp && !is_and_or(temp->var))
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
		}
		else
			temp = temp->next;
	}
	return (temp);
}

t_tok	*operator_jump_parentheses(t_tok *temp)
{
	int	parentheses;

	while (temp && !is_operator(temp->var))
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
		}
		else
			temp = temp->next;
	}
	return (temp);
}

t_tok	*pipe_reverse_jump_parentheses(t_tok *temp)
{
	int	parentheses;

	while (temp && ft_strncmp(temp->var, "|", 2) != 0)
	{
		if (temp && ft_strncmp(temp->var, ")", 2) == 0)
		{
			parentheses = reverse_number_of_parentheses(temp);
			while (temp && parentheses > 0)
			{
				if (temp && ft_strncmp(temp->var, "(", 2) == 0)
					parentheses--;
				temp = temp->prev;
			}
		}
		else
			temp = temp->prev;
	}
	return (temp);
}

t_tok	*and_or_reverse_jump_parentheses(t_tok *temp)
{
	int	parentheses;

	while (temp && !is_and_or(temp->var))
	{
		if (temp && ft_strncmp(temp->var, ")", 2) == 0)
		{
			parentheses = reverse_number_of_parentheses(temp);
			while (temp && parentheses > 0)
			{
				if (temp && ft_strncmp(temp->var, "(", 2) == 0)
					parentheses--;
				temp = temp->prev;
			}
		}
		else
			temp = temp->prev;
	}
	return (temp);
}
