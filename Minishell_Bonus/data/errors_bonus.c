/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:58:14 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/10 10:23:38 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_parenthese(char *str)
{
	if (ft_strncmp(str, "(", 2) == 0 || ft_strncmp(str, ")", 2) == 0)
		return (TRUE);
	return (FALSE);
}

static int	first_parenthese_check(t_tok *tempstart)
{
	while (tempstart)
	{
		if (!is_operator(tempstart->var) && !is_parenthese(tempstart->var)
			&& tempstart->next && !ft_strncmp(tempstart->next->var, "(", 2))
			return (printf("Invalid syntax: unexpected parenthese\n"));
		else if (!ft_strncmp(tempstart->var, ")", 2) && tempstart->next
			&& !is_operator(tempstart->next->var)
			&& ft_strncmp(tempstart->next->var, ")", 2))
			return (printf("Invalid syntax: no operator after parenthese\n"));
		else if (!ft_strncmp(tempstart->var, "(", 2) && tempstart->next
			&& !ft_strncmp(tempstart->next->var, ")", 2))
			return (printf("Invalid syntax: nothing inside parentheses\n"));
		tempstart = tempstart->next;
	}
	return (EXIT_SUCCESS);
}

static int	second_parenthese_check(t_tok *tempstart)
{
	int		open_par;
	int		c;
	int		diff;

	open_par = 0;
	c = 0;
	diff = 0;
	while (tempstart)
	{
		if (tempstart && !ft_strncmp(tempstart->var, ")", 2) && open_par == 0)
			return (printf("Invalid syntax: unexpected parenthese\n"));
		if (tempstart && !ft_strncmp(tempstart->var, "(", 2))
		{
			open_par++;
			if (number_of_parentheses(tempstart) < 0)
				return (EXIT_FAILURE);
			c = number_of_parentheses(tempstart);
			tempstart = go_to_first_closed_parenthese(tempstart, &c, &diff);
			tempstart = go_to_last_closed_parenthese(tempstart, &c, &diff);
			open_par--;
		}
		else
			tempstart = tempstart->next;
	}
	return (EXIT_SUCCESS);
}

int	bonus_errors(t_shell *shell)
{
	t_tok	*tempstart;
	t_tok	*tempend;

	tempstart = shell->user_command->start;
	tempend = shell->user_command->end;
	if ((is_operator(tempstart->var) && tempstart->quote == 0)
		|| (is_operator(tempend->var) && tempend->quote == 0))
		return (printf("Invalid syntax: operator at beginning or end\n"));
	if (first_parenthese_check(tempstart))
		return (EXIT_FAILURE);
	tempstart = shell->user_command->start;
	if (second_parenthese_check(tempstart))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
