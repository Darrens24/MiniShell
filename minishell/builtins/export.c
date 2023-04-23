/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:21:54 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/23 13:53:52 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*find_export_args(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp && ft_strncmp(temp->var, "export", 7) != 0)
		temp = temp->next;
	temp = temp->next;
	return (temp);
}

int	export_ascii_sorted(t_tok *temp, t_chained *sorted_env)
{
	t_node	*search;
	int		index;

	search = sorted_env->start;
	index = 0;
	while (search && ft_strncmp(temp->var, search->variable, (ft_strlen(search->variable) + ft_strlen(temp->var))) > 0)
	{
		index++;
		search = search->next;
	}
	if (index == 0)
		new_front_node(sorted_env, temp->var);
	else if (!search)
		new_back_node(sorted_env, temp->var);
	else
	{
		new_current_node(sorted_env, index, temp->var);
	}
	return (EXIT_SUCCESS);
}

int	equal_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	export_variable(t_shell *shell)
{
	t_tok	*temp;
	t_node	*node_to_remove;
	char	*var_before_equal;

	temp = find_export_args(shell);
	while (temp)
	{
		var_before_equal = ft_strndup(temp->var, 0, ft_strlenequal(temp->var));
		if (!valid_arg(var_before_equal))
			printf("export: '%s': not a valid identifier\n", temp->var);
		else if (!envchecker(var_before_equal, shell->sorted_env_l))
		{
			if (equal_in_string(temp->var))
				new_back_node(shell->env_l, temp->var);
			export_ascii_sorted(temp, shell->sorted_env_l);
		}
		else if (envchecker(var_before_equal, shell->sorted_env_l))
		{
			if (equal_in_string(temp->var))
			{
				if (envchecker(var_before_equal, shell->env_l))
				{
					node_to_remove = find_node_to_remove(var_before_equal, shell->env_l);
					printf("nodetoremove %s\n", node_to_remove->variable);
					remove_current_node(node_to_remove, shell->env_l);
					printf("cc3\n");
				}
				new_back_node(shell->env_l, temp->var);
				printf("cc4\n");
			}
			else if (!equal_in_string(temp->var))
				return (EXIT_FAILURE);
			node_to_remove = find_node_to_remove(var_before_equal, shell->sorted_env_l);
			remove_current_node(node_to_remove, shell->sorted_env_l);
			export_ascii_sorted(temp, shell->sorted_env_l);
		}
		free(var_before_equal);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

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
