/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/18 18:46:54 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_trinary_tree(t_toklst *user_command, t_shell *shell)
{
	t_tree		*tree;
	t_tok		*temp;
	t_branch	*temp_branch;
	int			i;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return ;
	temp = user_command->start;
	i = 0;
	create_start_branch(tree, shell, i++);
	if (no_parentheses(user_command))
		classic_fill();
	else
	{
		while (temp->next->next && ft_strncmp(temp->next->next->var, "(", 2) != 0)
		{
			create_middle_branch(tree, shell, &i);
			temp = temp->next;
		}

	}
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

t_tree	*create_start_branch(t_tree *tree, t_shell *shell, int i)
{
	t_branch	*new_branch;

	tree->nb_elem = 0;
	new_branch = malloc(sizeof(t_branch));
	if (!new_branch)
		return (0);
	new_branch->left = NULL;
	new_branch->middle = NULL;
	new_branch->right = NULL;
	new_branch->cmd = shell->multi_cmd[i];
	tree->start = new_branch;
	tree->nb_elem++;
	return (tree);
}

t_tree	*create_middle_branch(t_tree *tree, t_toklst *user_command)
{
	t_branch	*branch;
	t_branch	*temp;
	t_tok		*cmd;

	branch = malloc(sizeof(t_branch));
	if (!branch)
		return (0);
	branch->left = NULL;
	branch->middle = NULL;
	branch->right = NULL;
	cmd = user_command->start;
	branch->cmd = malloc(sizeof(char *) * 10);
	if (!branch->cmd)
		return (0);
	fill_tree_command(cmd, branch);
	temp = tree->start;
	while (temp)
		temp = temp->middle;
	temp->middle = branch;
	return (tree);
}
void	fill_tree_command(t_tok *cmd, t_branch *branch)
{
	int	i;

	i = 0;
	while (cmd && !is_operator(cmd->var))
	{
		branch->cmd[i++] = ft_strdup(cmd->var);
		cmd = cmd->next;
	}
	branch->cmd[i] = NULL;
}

int	is_operator(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0
		|| ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}
/*
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
*/
