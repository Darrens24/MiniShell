/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:21:54 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/03 17:01:36 by eleleux          ###   ########.fr       */
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
		index--;
		new_current_node(sorted_env, index, temp->var); 
	}
	return (EXIT_SUCCESS);
}

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || !ft_isalpha(arg[i]))
		return (FALSE);
	return (TRUE);
}

int	export_variable(t_shell *shell)
{
	t_tok	*temp;
	t_node	*node_to_remove;
	int		index;
	char	*var_before_equal;

	temp = find_export_args(shell);
	while (temp)
	{
		var_before_equal = ft_strndup(temp->var, 0, ft_strlenequal(temp->var));
		if (!valid_arg(var_before_equal))
			printf("export: '%s': not a valid identifier\n", temp->var);
		else if (!envchecker(var_before_equal, shell->sorted_env_l))
			export_ascii_sorted(temp, shell->sorted_env_l);
		else if (envchecker(var_before_equal, shell->sorted_env_l))
		{
			index = envindex(var_before_equal, shell->sorted_env_l);
			node_to_remove = find_node_to_remove(var_before_equal, shell->sorted_env_l);
			remove_current_node(node_to_remove, shell->sorted_env_l);
			if (index == 0)
				new_front_node(shell->sorted_env_l, temp->var);
			else
				new_current_node(shell->sorted_env_l, index - 1, temp->var);
		}
		free(var_before_equal);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
