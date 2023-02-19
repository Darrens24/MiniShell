/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:28:55 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/19 16:51:57 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export(t_shell *shell)
{
	t_node	*temp;

	temp = shell->sorted_env_l->start;
	while (temp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		printf("%s\n", temp->variable);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	print_echo(char **command)
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
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (tmp)
		ft_putstr_fd("", STDOUT_FILENO);
	else
		ft_putendl_fd("", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	unset_variable(t_shell *shell)
{
	t_node	*temp;

	temp = shell->sorted_env_l->end;
	while (temp && ft_strncmp(temp->variable,
			shell->user_command->start->next->var,
			ft_strlenequal(temp->variable)))
		temp = temp->prev;
	if (shell->sorted_env_l->nb_elem == 1)
		remove_back_node(shell->sorted_env_l);
	else if (temp)
		remove_current_node(temp, shell->sorted_env_l);
	return (EXIT_SUCCESS);
}

int	export_variable(t_shell *shell)
{
	if (!envchecker(ft_strndup(shell->user_command->start->next->var,
				0, ft_strlenequal(shell->user_command->start->next->var)),
			shell->sorted_env_l))
		new_back_node(shell->sorted_env_l,
			shell->user_command->start->next->var);
	else
	{
		unset_variable(shell);
		new_back_node(shell->sorted_env_l,
			shell->user_command->start->next->var);
	}
	return (EXIT_SUCCESS);
}

int	execute_builtin_cmd(t_shell *shell, int i)
{
	execute_directory_cmd(shell, i);
	if (ft_strncmp(shell->multi_cmd[i][0], "env", 4) == 0)
	{
		if (argument_after_cmd(shell) == true)
			return (printf("Env command won't take arguments or options\n"));
		return (print_list(shell->env_l), EXIT_SUCCESS);
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "export", 7) == 0)
	{
		if (argument_after_cmd(shell) == false)
			return (print_export(shell));
		else
			return (export_variable(shell));
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "unset", 6) == 0)
	{
		if (argument_after_cmd(shell) == false)
			return (EXIT_SUCCESS);
		else
			return (unset_variable(shell));
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "echo", 5) == 0)
		print_echo(shell->multi_cmd[i]);
	return (EXIT_SUCCESS);
}
