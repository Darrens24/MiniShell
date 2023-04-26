/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:07:37 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/26 18:25:19 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_branch	*left_branch;

	left_branch = malloc(sizeof(t_branch));
	if (!left_branch)
		return (0);
	left_branch->right = NULL;
	left_branch->left = NULL;
	left_branch->dad = map;
	left_branch->cmd = give_active_command(left_branch->dad->left_command);
	//printf("left cmd is %s\n", left_branch->cmd[0]);
	if (map && operator_in_cmd(map->left_command))
	{
		left_branch->left_command = split_left(left_branch->dad->left_command);//si fini on doit stop
		left_branch->right_command = split_right(left_branch->dad->left_command);
	}
	else if (map && !is_operator(left_branch->cmd[0]))
	{
		left_branch->left_command = NULL;
		left_branch->right_command = NULL;
	}
	//printf("ca va segfault dans left leaf!!\n");
	left_branch->err_code = -1;
	map->left = left_branch;
	return (left_branch);
}

t_branch	*create_right_leaf(t_branch *map)
{
	t_branch	*right_branch;

	right_branch = malloc(sizeof(t_branch));
	if (!right_branch)
		return (0);
	right_branch->right = NULL;
	right_branch->left = NULL;
	right_branch->dad = map;
	right_branch->cmd = give_active_command(right_branch->dad->right_command);
	//printf("right cmd is %s\n", right_branch->cmd[0]);
	if (map && operator_in_cmd(map->right_command))
	{
		right_branch->left_command = split_left(right_branch->dad->right_command);
		right_branch->right_command = split_right(right_branch->dad->right_command);
	}
	else if (map && !is_operator(right_branch->cmd[0]))
	{
		right_branch->left_command = NULL;
		right_branch->right_command = NULL;
	}
	right_branch->err_code = -1;
	map->right = right_branch;
	return (right_branch);
}