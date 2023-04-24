/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:45:17 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/24 11:00:35 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	norm_checker(t_tok *tok)
{
	if (ft_strlen(tok->var) > 2 || (!tok->prev && tok->var[0] != '<'
			&& tok->var[0] != '>') || !tok->next || (tok->prev
			&& tok->prev->var && tok->prev->var[0]
			&& tok->prev->var[0] == '>' && tok->prev->quote == 0)
		|| (tok->prev && tok->prev->var && tok->prev->var[0]
			&& tok->prev->var[0] == '&' && tok->prev->quote == 0)
		|| (tok->prev && tok->prev->var && tok->prev->var[0]
			&& tok->prev->var[0] == '|' && tok->prev->quote == 0)
		|| (tok->prev && tok->prev->var && tok->prev->var[0]
			&& tok->prev->var[0] == '<' && tok->prev->quote == 0)
		|| (tok->next->var && tok->next->var[0]
			&& tok->next->var[0] == '>' && tok->next->quote == 0)
		|| (tok->next->var && tok->next->var[0]
			&& tok->next->var[0] == '&' && tok->next->quote == 0)
		|| (tok->next->var
			&& tok->next->var[0] && tok->next->var[0] == '|'
			&& tok->next->quote == 0)
		|| (tok->next->var && tok->next->var[0]
			&& tok->next->var[0] == '<' && tok->next->quote == 0))
		return (1);
	return (0);
}

int	token_checker(t_shell *shell)
{
	t_tok	*tok;

	tok = shell->user_command->start;
	while (tok)
	{
		if (tok->var && tok->var[0] && tok->quote == 0)
			if (tok->var[0] == '>' || tok->var[0] == '&' || tok->var[0] == '|'
				|| tok->var[0] == '<')
				if (norm_checker(tok))
					return (TRUE);
		tok = tok->next;
	}
	return (FALSE);
}
