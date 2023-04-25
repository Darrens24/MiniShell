/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:21:54 by eleleux           #+#    #+#             */
/*   Updated: 2023/03/10 13:22:36 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_node	*temp;
	t_node	*temp2;
	char	*temp3;
	t_tok	*search;

	search = shell->user_command->start->next;
	while (search)
	{
		temp3 = ft_strndup(search->var,
				0, ft_strlenequal(search->var));
		temp = shell->sorted_env_l->end;
		temp2 = shell->env_l->end;
		while (temp && ft_strncmp(temp->variable,
				search->var,
				ft_strlenequal(temp->variable)))
			temp = temp->prev;
		while (temp2 && ft_strncmp(temp2->variable,
				search->var,
				ft_strlenequal(temp2->variable)))
			temp2 = temp2->prev;
		clean_export_list(shell, temp3, temp, temp2);
		search = search->next;
		free(temp3);
	}
	return (EXIT_SUCCESS);
}

int	export_variable(t_shell *shell)
{
	int		index;
	char	*temp;

	temp = ft_strndup(shell->user_command->start->next->var,
			0, ft_strlenequal(shell->user_command->start->next->var));
	index = 0;
	if (!envchecker(temp, shell->sorted_env_l))
		new_back_node(shell->sorted_env_l,
			shell->user_command->start->next->var);
	else if (ft_strchr(shell->user_command->start->next->var, '=') != 0)
	{
		index = envindex(temp, shell->sorted_env_l);
		unset_variable(shell);
		new_current_node(shell->sorted_env_l, index,
			shell->user_command->start->next->var);
	}
	if (ft_strchr(shell->user_command->start->next->var, '=') != 0)
		new_back_node(shell->env_l,
			shell->user_command->start->next->var);
	remove_current_tok(shell->user_command->start->next, shell->user_command);
	free(temp);
	if (shell->user_command->start->next)
		export_variable(shell);
	return (EXIT_SUCCESS);
}
