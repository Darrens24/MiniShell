/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:33:41 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/09 09:00:52 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_b_variable(t_shell *shell, char **command)
{
	t_unset	*uns;

	uns = malloc(sizeof(t_unset));
	if (!uns)
		return (EXIT_FAILURE);
	uns->env_node = shell->env_l->start;
	uns->i = 1;
	while (command[uns->i])
	{
		uns->var = ft_strndup(command[uns->i], 0, ft_strlen(command[uns->i]));
		if (!valid_arg(uns->var))
			printf("unset: '%s': not a valid identifier\n", command[uns->i]);
		else if (envchecker(uns->var, shell->sorted_env_l))
		{
			uns->export_node = find_node_to_remove(uns->var,
					shell->sorted_env_l);
			remove_current_node(uns->export_node, shell->sorted_env_l);
		}
		if (envchecker(uns->var, shell->env_l))
			norm_unset(uns, shell);
		free(uns->var);
		uns->i++;
	}
	free(uns);
	return (EXIT_SUCCESS);
}
