/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:21:54 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/09 08:59:18 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_b_ascii_sorted(char *cmd, t_chained *sorted_env)
{
	t_node	*search;
	int		index;

	search = sorted_env->start;
	index = 0;
	while (search && ft_strncmp(cmd, search->variable,
			(ft_strlen(search->variable) + ft_strlen(cmd))) > 0)
	{
		index++;
		search = search->next;
	}
	if (index == 0)
		new_front_node(sorted_env, cmd);
	else if (!search)
	{
		new_back_node(sorted_env, cmd);
	}
	else
		new_current_node(sorted_env, index, cmd);
	return (EXIT_SUCCESS);
}

static void	variable_b_is_in_env(char *var, t_shell *shell, char *cmd)
{
	t_node	*node_to_remove;

	if (equal_in_string(cmd))
	{
		if (envchecker(var, shell->env_l))
		{
			node_to_remove = find_node_to_remove(var,
					shell->env_l);
			remove_current_node(node_to_remove, shell->env_l);
		}
		new_back_node(shell->env_l, cmd);
	}
	else if (!equal_in_string(cmd))
		return ;
	node_to_remove = find_node_to_remove(var,
			shell->sorted_env_l);
	remove_current_node(node_to_remove, shell->sorted_env_l);
	export_b_ascii_sorted(cmd, shell->sorted_env_l);
}

int	export_b_variable(t_shell *shell, char **command)
{
	char	*var_before_equal;
	int		i;

	i = 1;
	while (command[i])
	{
		var_before_equal = ft_strndup(command[i], 0,
				ft_strlenequal(command[i]));
		if (!valid_arg(var_before_equal))
			printf("export: '%s': not a valid identifier\n", command[i]);
		else if (!envchecker(var_before_equal, shell->sorted_env_l))
		{
			if (equal_in_string(command[i]))
				new_back_node(shell->env_l, command[i]);
			export_b_ascii_sorted(command[i], shell->sorted_env_l);
		}
		else if (envchecker(var_before_equal, shell->sorted_env_l))
			variable_b_is_in_env(var_before_equal, shell, command[i]);
		free(var_before_equal);
		i++;
	}
	return (EXIT_SUCCESS);
}
