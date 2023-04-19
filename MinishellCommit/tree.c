/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/19 13:32:14 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_parentheses(t_toklst *user_command)
{
	t_tok	*temp;
	int		count;
	int		diff;

	temp = user_command->start;
	count = 0;
	diff = 0;
	while (temp && ft_strncmp(temp->var, ")", 2) != 0)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
		{
			count++;
			diff++;
		}
		temp = temp->next;
	}
	if (temp && ft_strncmp(temp->var, ")", 2) == 0)
	{
		diff--;
		temp = temp->next;
	}
	while (temp && diff > 0)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
		{
			count++;
			diff++;
		}
		else if (temp && ft_strncmp(temp->var, ")", 2) == 0)
			diff--;
		temp = temp->next;
	}
	if (diff > 0)
	{
		printf("Parenthesis not closed\n");
		return (-1);
	}
	return (count);
}

void	fill_trinary_tree(t_toklst *user_command, t_shell *shell)
{
	t_tok		*temp;
	int			par;

	shell->tree = malloc(sizeof(t_tree));
	if (!shell->tree)
		return ;
	shell->tree = create_start_branch(shell->tree, user_command);
	temp = user_command->start;
	while (temp && ft_strncmp(temp->var, "(", 2) != 0)
	{
		create_middle_branch(shell->tree, user_command);
		temp = user_command->start;
	}
	par = 0;
	if (temp && ft_strncmp(temp->var, "(", 2) == 0)
		par = number_of_parentheses(user_command);
		//create_ast_branches(shell->tree, user_command);
	printf("nb of par is %d\n", par);
	/*
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
	*/
}

t_tree	*create_start_branch(t_tree *tree, t_toklst *user_command)
{
	t_branch	*new_branch;

	tree->nb_elem = 0;
	new_branch = malloc(sizeof(t_branch));
	if (!new_branch)
		return (0);
	new_branch->left = NULL;
	new_branch->middle = NULL;
	new_branch->right = NULL;
	fill_tree_command_remove_tok(user_command, new_branch);
	tree->start = new_branch;
	tree->nb_elem++;
	return (tree);
}

t_tree	*create_middle_branch(t_tree *tree, t_toklst *user_command)
{
	t_branch	*branch;
	t_branch	*temp;

	branch = malloc(sizeof(t_branch));
	if (!branch)
		return (0);
	branch->left = NULL;
	branch->middle = NULL;
	branch->right = NULL;
	fill_tree_command_remove_tok(user_command, branch);
	temp = tree->start;
	while (temp->middle)
		temp = temp->middle;
	temp->middle = branch;
	return (tree);
}

void	fill_tree_command_remove_tok(t_toklst *user_command, t_branch *branch)
{
	int		i;
	t_tok	*cmd;

	branch->cmd = malloc(sizeof(char *) * 30);
	if (!branch->cmd)
		return ;
	i = 0;
	cmd = user_command->start;
	if (!is_operator(cmd->var))
	{
		while (cmd && !is_operator(cmd->var))
		{
			branch->cmd[i++] = ft_strdup(cmd->var);
			cmd = cmd->next;
			remove_front_tok(user_command);
		}
	}
	else
	{
		branch->cmd[i++] = ft_strdup(cmd->var);
		remove_front_tok(user_command);
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
