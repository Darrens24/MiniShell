/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:25:59 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/05 14:15:00 by pfaria-d         ###   ########.fr       */
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

/*
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
*/

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

/*
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
*/
