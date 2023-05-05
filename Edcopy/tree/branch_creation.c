/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:07:37 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/04 18:02:20 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*create_start_branch(t_tree *tree, t_tok *temp, t_toklst *user_command)
{
	t_branch	*branch;

	branch = malloc(sizeof(t_branch));
	if (!branch)
		return (0);
	branch->left = NULL;
	branch->right = NULL;
	branch->dad = NULL;
	branch->cmd = malloc(sizeof(char *) * 2);
	branch->cmd_block = 0;
	if (!branch->cmd)
		return (0);
	branch->cmd[0] = ft_strdup(temp->var);
	branch->cmd[1] = NULL;
	branch->left_command = split_left(user_command);
	branch->right_command = split_right(user_command);
	branch->err_code = -1;
	tree->start = branch;
	tree->map = tree->start;
	return (tree);
}

t_branch	*create_left_leaf(t_branch *map)
{
	t_branch	*l_branch;

	l_branch = malloc(sizeof(t_branch));
	if (!l_branch)
		return (0);
	l_branch->right = NULL;
	l_branch->left = NULL;
	l_branch->dad = map;
	l_branch->cmd = give_active_command(l_branch->dad->left_command);
	l_branch->cmd_block = l_branch->dad->left_command->start->prio;
	if (map && operator_in_cmd(map->left_command))
	{
		l_branch->left_command = split_left(l_branch->dad->left_command);
        l_branch->cmd_block = l_branch->left_command->start->prio;
		l_branch->right_command = split_right(l_branch->dad->left_command);
        l_branch->cmd_block = l_branch->right_command->start->prio;
	}
	else if (map && !is_operator(l_branch->cmd[0]))
	{
		l_branch->left_command = NULL;
		l_branch->right_command = NULL;
        l_branch->cmd_block = map->cmd_block;
	}
	l_branch->err_code = -1;
	map->left = l_branch;
	return (l_branch);
}

t_branch	*create_right_leaf(t_branch *map)
{
	t_branch	*r_branch;

	r_branch = malloc(sizeof(t_branch));
	if (!r_branch)
		return (0);
	r_branch->right = NULL;
	r_branch->left = NULL;
	r_branch->dad = map;
	r_branch->cmd = give_active_command(r_branch->dad->right_command);
	r_branch->cmd_block = 0;
	if (map && operator_in_cmd(map->right_command))
	{
		r_branch->left_command = split_left(r_branch->dad->right_command);
        r_branch->cmd_block = r_branch->left_command->start->prio;
		r_branch->right_command = split_right(r_branch->dad->right_command);
        r_branch->cmd_block = r_branch->right_command->start->prio;
	}
	else if (map && !is_operator(r_branch->cmd[0]))
	{
		r_branch->left_command = NULL;
		r_branch->right_command = NULL;
        r_branch->cmd_block = map->cmd_block;
	}
	r_branch->err_code = -1;
	map->right = r_branch;
	return (r_branch);
}
