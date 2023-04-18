/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/18 15:17:53 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    test(t_toklst *user_command, t_shell *shell)
{
	t_tree  	*tree;
	t_tok   	*temp;
	t_branch	*temp_branch;
	int     	i;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return ;
	temp = user_command->start;
	i = 0;
	create_start_branch(tree, shell, i);
	i++;
	temp = temp->next;
	temp_branch = tree->start;
	while (temp)
	{
		if (ft_strncmp(temp->var, "|", 2) != 0)
			create_left_branch(tree, shell, i);
		else if (ft_strncmp(temp->var, "|", 2) == 0)
			create_right_branch(tree, shell, i);
		temp = temp->next;
	}
}

t_tree    *create_start_branch(t_tree *tree, t_shell *shell, int i)
{
	t_branch    *new_branch;

	tree->nb_elem = 0;
	new_branch = malloc(sizeof(t_branch));
	if (!new_branch)
		return (0);
	new_branch->left = NULL;
	new_branch->right = NULL;
	new_branch->cmd = shell->multi_cmd[i];
	tree->start = new_branch;
	tree->nb_elem++;
	return (tree);
}

t_tree    *create_right_branch(t_tree *tree, t_shell *shell, int i)
{
	t_branch    *new_branch;

	new_branch = malloc(sizeof(t_branch));
	if (!new_branch)
		return (0);
	new_branch->left = NULL;
	new_branch->right = NULL;
	new_branch->code = code;
	new_branch->cmd = shell->multi_cmd[i];
	tree->nb_elem++;
	return (tree);
}

t_tree    *create_left_branch(t_tree *tree, t_shell *shell, int i, int code)
{
	t_branch    *new_branch;

	new_branch = malloc(sizeof(t_branch));
	if (!new_branch)
		return (0);
	new_branch->left = NULL;
	new_branch->right = NULL;
	new_branch->code = code;
	new_branch->cmd = shell->multi_cmd[i];
	tree->nb_elem++;
	return (tree);
}
