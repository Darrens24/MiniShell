/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:21:54 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/05 12:14:08 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	put_quotes_to_export(char *variable)
{
	int	i;

	i = 0;
	while (variable[i] && variable[i] != '=')
	{
		ft_putchar_fd(variable[i], 1);
		i++;
	}
	if (variable[i])
	{
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
		i++;
	}
	while (variable[i])
	{
		ft_putchar_fd(variable[i], 1);
		i++;
	}
	if (equal_in_string(variable))
		ft_putchar_fd('\"', 1);
}

int	print_export(t_shell *shell)
{
	t_node	*temp;

	temp = shell->sorted_env_l->start;
	while (temp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		put_quotes_to_export(temp->variable);
		ft_putchar_fd('\n', STDOUT_FILENO);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	clean_export_list(t_shell *shell, char *temp3, t_node *temp, t_node *temp2)
{
	if (shell->sorted_env_l->nb_elem == 1)
	{
		remove_back_node(shell->sorted_env_l);
		if (envchecker(temp3, shell->env_l))
			remove_back_node(shell->env_l);
	}
	else if (temp)
	{
		if (envchecker(temp3, shell->sorted_env_l))
			remove_current_node(temp, shell->sorted_env_l);
		if (envchecker(temp3, shell->env_l))
			remove_current_node(temp2, shell->env_l);
	}
	return (EXIT_SUCCESS);
}
*/
