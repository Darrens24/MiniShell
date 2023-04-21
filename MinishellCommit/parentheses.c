/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:57:42 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/21 14:35:04 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*go_to_first_closed_parenthese(t_tok *temp, int *count, int *diff)
{
	while (temp && ft_strncmp(temp->var, ")", 2) != 0)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
		{
			*count += 1;
			*diff += 1;
		}
		temp = temp->next;
	}
	if (temp && ft_strncmp(temp->var, ")", 2) == 0)
	{
		*diff -= 1;
		temp = temp->next;
	}
	return (temp);
}

t_tok	*go_to_last_closed_parenthese(t_tok *temp, int *count, int *diff)
{
	while (temp && diff > 0)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
		{
			*count += 1;
			*diff += 1;
		}
		else if (temp && ft_strncmp(temp->var, ")", 2) == 0)
			*diff -= 1;
		temp = temp->next;
	}
	return (temp);
}

t_tok	*go_to_last_opened_parenthese(t_tok *temp, int *count, int *diff)
{
	temp = go_to_reverse_parenthese(temp, count, diff);
	while (temp && diff > 0)
	{
		if (temp && ft_strncmp(temp->var, ")", 2) == 0)
		{
			*count += 1;
			*diff += 1;
		}
		else if (temp && ft_strncmp(temp->var, "(", 2) == 0)
			*diff -= 1;
		temp = temp->next;
	}
	return (temp);
}

int	number_of_parentheses(t_tok *temp)
{
	int		count;
	int		diff;

	count = 0;
	diff = 0;
	temp = go_to_first_closed_parenthese(temp, &count, &diff);
	temp = go_to_last_closed_parenthese(temp, &count, &diff);
	if (diff > 0)
	{
		printf("Parenthesis not closed\n");
		return (-1);
	}
	return (count);
}

t_tok	*go_to_reverse_parenthese(t_tok *temp, int *count, int *diff)
{
	while (temp && ft_strncmp(temp->var, "(", 2) != 0)
	{
		if (temp && ft_strncmp(temp->var, ")", 2) == 0)
		{
			*count += 1;
			*diff += 1;
		}
		temp = temp->prev;
	}
	if (temp && ft_strncmp(temp->var, "(", 2) == 0)
	{
		*diff -= 1;
		temp = temp->prev;
	}
	return (temp);
}

int	reverse_number_of_parentheses(t_tok *temp)
{
	int		count;
	int		diff;

	count = 0;
	diff = 0;
	temp = go_to_reverse_parenthese(temp, &count, &diff);
	while (temp && diff > 0)
	{
		if (temp && ft_strncmp(temp->var, ")", 2) == 0)
		{
			count++;
			diff++;
		}
		else if (temp && ft_strncmp(temp->var, "(", 2) == 0)
			diff--;
		temp = temp->prev;
	}
	return (count);
}
