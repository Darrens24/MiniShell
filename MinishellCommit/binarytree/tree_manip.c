/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:59:43 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/24 11:29:28 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_treenode(t_treenode *root, char **command)
{
	t_treenode	*node;
	t_treenode	*temp;

	node = malloc(sizeof(t_treenode));
	node->left = NULL;
	node->right = NULL;
	node->command = command;
	temp = root;
	if (!root)
	{
		root = node;
		return ;
	}
	if (control_operator) //check la user command
		root->right = node;
	else
	{
		while (temp)
			temp = temp->left;
	}

}

void	print_tree(t_treenode *tree) //a supprimer a la fin
{

}
