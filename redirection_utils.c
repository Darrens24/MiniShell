/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:31:06 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/06 14:32:47 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_infile_redirection(t_toklst *user_command)
{
	if ((ft_strncmp(user_command->start->var, "<", 2) == 0)
		|| (ft_strncmp(user_command->start->var, "<<", 3) == 0))
			return (TRUE);
	return (FALSE);
}

int	is_outfile_redirection(t_toklst *user_command)
{
	if (user_command->end->prev && ((ft_strncmp(user_command->end->prev->var, ">", 2) == 0)
		|| (ft_strncmp(user_command->end->prev->var, ">>", 3) == 0)))
			return (TRUE);
	return (FALSE);
}

int	delete_operator_and_outfile(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < 2)
		remove_back_tok(shell->user_command);
	return (EXIT_SUCCESS);
}

int	delete_operator_and_infile(t_shell *shell)
{
	int	i;

	if (shell->user_command->nb_elem == 0)
		return (EXIT_SUCCESS);
	i = -1;
	while (++i < 2)
		remove_front_tok(shell->user_command);
	return (EXIT_SUCCESS);
}

char	*append_newline(char *limiter)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(limiter) + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (limiter[i])
	{
		result[i] = limiter[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
}

