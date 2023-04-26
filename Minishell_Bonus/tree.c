/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/26 11:19:51 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*go_to_branch_start(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->end;
	if (temp && and_or_in_cmd_outside_parentheses(user_command))
		while (temp && !is_and_or(temp->var))
		{
			if (temp && ft_strncmp(temp->var, ")", 2) == 0)
				return (and_or_reverse_jump_parentheses(temp));
			temp = temp->prev;
		}
	else if (temp && pipe_in_cmd_outside_parentheses(user_command))
		while (temp && !is_operator(temp->var))
		{
			if (temp && ft_strncmp(temp->var, ")", 2) == 0)
				return (pipe_reverse_jump_parentheses(temp));
			temp = temp->prev;
		}
	else if (temp && ft_strncmp(temp->var, ")", 2) == 0)
	{
		remove_front_tok(user_command);
		remove_back_tok(user_command);
		temp = go_to_branch_start(user_command);
	}
	return (temp);
}

t_tree	*get_new_start_split_command(t_shell *shell, t_branch *map)
{
	/*static int	i = 0;
	if (i == 10)
		exit(1);
	i++;
	*/
	if (map && map->left_command)
	{

		create_left_leaf(map);
		clear_toklst(map->left_command);
		free(map->left_command);
		map->left_command = NULL;
		get_new_start_split_command(shell, map->left);
	}
	else if (map && map->right_command)
	{
		create_right_leaf(map);
		clear_toklst(map->right_command);
		free(map->right_command);
		map->right_command = NULL;
		get_new_start_split_command(shell, map->right);
	}
	else if (map && map->dad)
	{
		//printf("dad\n");
		//map = map->dad;
		get_new_start_split_command(shell, map->dad);
	}
	return (shell->tree);
}

/*
	if (left command existe)
		cree un node a gauche;
	if (plus de left commande)
		remonte
		if (right commande existe)
			cree un node a droite
	si aucun des 2
		remonte et recheck
*/

void print_tree_cmds(t_tree *tree)
{
    if (tree == NULL || tree->start == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    printf("Printing tree commands:\n");
    print_branch_cmds(tree->start);
}

void print_branch_cmds(t_branch *branch)
{
    if (branch == NULL) {
        return;
    }

    print_branch_cmds(branch->left);
    if (branch->cmd != NULL) {
        printf("%s\n", *(branch->cmd));
    }
    print_branch_cmds(branch->right);
}

void	fill_trinary_tree(t_toklst *user_command, t_shell *shell)
{
	t_tok		*temp;

	shell->tree = malloc(sizeof(t_tree));
	if (!shell->tree)
		return ;
	temp = user_command->start;
	temp = go_to_branch_start(user_command);
	shell->tree = create_start_branch(shell->tree, temp, user_command);
	/*
	printf("start is %s\n", shell->tree->start->cmd[0]);
	printf("startleft is %s\n", shell->tree->start->left_command->start->var);
	printf("startleft2 is %s\n", shell->tree->start->left_command->start->next->var);
	printf("startleft3 is %s\n", shell->tree->start->left_command->start->next->next->var);
	printf("startleft4 is %s\n", shell->tree->start->left_command->start->next->next->next->var);
	printf("startleft5 is %s\n", shell->tree->start->left_command->start->next->next->next->next->var);
	printf("startleft6 is %s\n", shell->tree->start->left_command->start->next->next->next->next->next->var);
	printf("startright is %s\n", shell->tree->start->right_command->start->var);
	*/
	shell->tree = get_new_start_split_command(shell, shell->tree->map);
	//print_tree_cmds(shell->tree);
	//create_ast_branches(shell->tree, shell);
}
/*
t_tree	*create_ast_branches(t_tree *tree, t_shell *shell)
{
	t_branch	*travel;
	t_branch	*leaf;
	t_tok		*temp;


	leaf = malloc(sizeof(t_branch));
	if (!leaf)
		return (0);
	travel = tree->map;
	temp = shell->user_command->start;
	if (temp && and_or_in_cmd_outside_parentheses(shell->user_command))	
	{
		travel->left = create_operator_leaf(shell->user_command, travel);
		travel->left = create_leaf_list(shell->user_command, travel);
		travel->left->dad = travel;
		travel->right = create_leaf_list(shell->user_command, travel);
		travel->right->dad = travel;
	}
	return (shell->tree);
}
*/




