/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:33:41 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/03 16:38:00 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*find_unset_args(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp && ft_strncmp(temp->var, "unset", 6) != 0)
		temp = temp->next;
	temp = temp->next;
	return (temp);
}

t_node	*find_node_to_remove(char *var_before_equal, t_chained *lst)
{
	t_node	*temp;	

	temp = lst->start;
	while (temp)
	{
		if (ft_strncmp(var_before_equal, temp->variable, ft_strlenequal(temp->variable)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (temp);
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

int	unset_variable(t_shell *shell)
{
	t_tok	*temp;
	t_node	*env_node;
	t_node	*export_node;
	char	*var_before_equal;

	temp = find_unset_args(shell);
	env_node = shell->env_l->start;
	while (temp)
	{
		var_before_equal = ft_strndup(temp->var, 0, ft_strlen(temp->var));
		if (!valid_arg(var_before_equal))
			printf("unset: '%s': not a valid identifier\n", temp->var);
		else if (envchecker(var_before_equal, shell->sorted_env_l))
		{
			export_node = find_node_to_remove(var_before_equal, shell->sorted_env_l);
			remove_current_node(export_node, shell->sorted_env_l);
		}
		if (envchecker(var_before_equal, shell->env_l))
		{
			env_node = find_node_to_remove(var_before_equal, shell->env_l);
			remove_current_node(env_node, shell->env_l);
		}
		free(var_before_equal);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
