/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:25:59 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/09 08:57:01 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_b_echo(char **command, t_shell *shell)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = option_n(command, i);
	if (tmp && !command[option_njump(command, i)])
		return (EXIT_SUCCESS);
	else if (!command[i + 1])
		return (ft_putchar_fd('\n', STDOUT_FILENO), 1);
	if (tmp)
		i = option_njump(command, i);
	else
		i++;
	while (command[i])
	{
		ft_putstr_fd(command[i], STDOUT_FILENO);
		if (get_b_command(shell, i++, command) != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (tmp)
		ft_putstr_fd("", STDOUT_FILENO);
	else
		ft_putendl_fd("", STDOUT_FILENO);
	g_err = 0;
	return (EXIT_SUCCESS);
}

int	export_b_manager(t_shell *shell, char **command, int pipe)
{
	if (command[1] && pipe)
		return (EXIT_FAILURE);
	else if (!command[1])
		print_export(shell);
	else
		return (export_b_variable(shell, command));
	return (EXIT_SUCCESS);
}
