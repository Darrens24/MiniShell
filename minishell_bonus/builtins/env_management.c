/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:28:55 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/27 17:33:26 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_echo(char **command, t_shell *shell)
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
		if (get_command(shell, i++) != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (tmp)
		ft_putstr_fd("", STDOUT_FILENO);
	else
		ft_putendl_fd("", STDOUT_FILENO);
	g_err = 0;
	return (EXIT_SUCCESS);
}

int	pipe_in_command(t_toklst *cmd)
{
	t_tok	*tmp;

	tmp = cmd->start;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "|", 2 == 0))
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	export_manager(t_shell *shell, int i)
{
	if (!shell->multi_cmd[i][1])
		print_export(shell);
	else if (shell->multi_cmd[i][1] && pipe_in_command(shell->user_command))
		return (EXIT_FAILURE);
	else
		return (export_variable(shell));
	return (EXIT_SUCCESS);
}

int	execute_builtin_cmd(t_shell *shell, int i)
{
	execute_directory_cmd(shell, i);
	if (ft_strncmp(shell->multi_cmd[i][0], "exit", 5) == 0)
		exit_shell(shell);
	if (ft_strncmp(shell->multi_cmd[i][0], "env", 4) == 0)
	{
		if (shell->multi_cmd[i][1])
			return (printf("Env command won't take arguments or options\n"));
		print_list(shell->env_l);
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "export", 7) == 0)
		export_manager(shell, i);
	else if (ft_strncmp(shell->multi_cmd[i][0], "unset", 6) == 0)
	{
		if (argument_after_cmd(shell) == FALSE)
			return (EXIT_SUCCESS);
		else
			return (unset_variable(shell));
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "echo", 5) == 0)
		print_echo(shell->multi_cmd[i], shell);
	return (EXIT_SUCCESS);
}
