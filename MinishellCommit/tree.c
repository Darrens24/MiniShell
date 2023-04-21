/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/21 19:54:27 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_trinary_tree(t_toklst *user_command, t_shell *shell)
{
	t_tok		*temp;
	t_toklst	*right_command;

	shell->tree = malloc(sizeof(t_tree));
	if (!shell->tree)
		return ;
	temp = user_command->start;
	get_number_of_op(user_command, shell);
	tree_number_of_pipes(user_command, shell, 'l');
	temp = go_to_branch_start(user_command);
	create_start_branch(shell->tree, temp);
	right_command = malloc(sizeof(t_toklst));
	if (!right_command)
		return ;
	while (temp)
	{
		new_back_tok(right_command, temp->var, 0, ft_strlen(temp->var));
		temp = temp->next;
		if (temp)
			remove_current_tok(temp->prev, user_command);
	}
	remove_back_tok(user_command);
	create_ast_branches(shell->tree, shell, temp);
}

t_tok	*go_to_branch_start(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->end;
	temp = and_or_reverse_jump_parentheses(temp);
	if (!temp)
	{
		temp = user_command->end;
		temp = pipe_reverse_jump_parentheses(temp);
	}
	return (temp);	
}

t_tok	*go_to_first_and_or(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	temp = and_or_jump_parentheses(temp);
	return (temp);
}

t_tok	*go_to_first_operator(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	temp = operator_jump_parentheses(temp);
	return (temp);
}

t_tok	*go_to_next_pipe_before_operator(t_tok *temp)
{
	while (temp && ft_strncmp(temp->var, "|", 2) != 0)
	{
		temp = pipe_reverse_jump_parentheses(temp);
		if (ft_strncmp(temp->var, "|", 2) == 0)
			return (temp);
		else if (temp && temp->prev)
			temp = temp->prev;
	}
	return (0);
}

t_branch	*create_left_leaf(t_tree *tree, t_tok *temp)
{
	t_branch	*travel;
	t_branch	*leaf;
	int			i;

	leaf = malloc(sizeof(t_branch));
	if (!leaf)
		return (0);
	leaf->right = NULL;
	leaf->left = NULL;
	i = 0;
	while (temp && !is_operator(temp->var))
	{
		temp = temp->prev;
		i++;
	}
	leaf->cmd = malloc(sizeof(char *) * (i + 2));
	if (!leaf->cmd)
		return (0);
	if (i == 0)
	{
		leaf->cmd[0] = ft_strdup(temp->var);
		leaf->cmd[1] = NULL;
	}
	else
	{
		temp = temp->next;
		while (temp && !is_operator(temp->var))
		{
			leaf->cmd[i] = ft_strdup(temp->var);
			temp = temp->next;
			i++;
		}
		leaf->cmd[i] = NULL;
	}
	travel = tree->start;
	while (travel && travel->left)
		travel = travel->left;
	travel->left = leaf;
	leaf->dad = travel;
	return (travel);	
}
/*
void	get_and_or_outside_parenthesis(t_tree *tree, t_toklst *user_command, t_tok *temp)
{

}
*/
t_tree	*fill_tree_with_operator(t_shell *shell, t_tok *temp)
{
	temp = temp->prev;
	while (temp)
	{
		temp = and_or_reverse_jump_parentheses(temp);
		if (temp && is_and_or(temp->var))
			create_left_leaf(shell->tree, temp);
		if (temp && temp->prev)
			temp = temp->prev;
	}
	return (shell->tree);
}

t_tree	*fill_tree_with_pipes(t_shell *shell, t_tok *temp)
{
	while (temp)
	{
		temp = pipe_reverse_jump_parentheses(temp);
		if (temp && ft_strncmp(temp->var, "|", 2) == 0)
			create_left_leaf(shell->tree, temp);
		if (temp && temp->prev)
			temp = temp->prev;
	}
	return (shell->tree);
}

t_branch	*create_ending_leaf(t_shell *shell, t_tok *temp)
{
	t_branch	*leaf;
	int			i;

	leaf = malloc(sizeof(t_branch));
	if (!leaf)
		return (0);
	leaf->right = NULL;
	leaf->left = NULL;
	i = 0;
	while (temp && !is_operator(temp->var))
	{
		i++;
		temp = temp->next;
	}
	leaf->cmd = malloc(sizeof(char *) * (i + 2));
	if (!leaf->cmd)
		return (0);
	i = 0;
	temp = shell->user_command->start;
	while (temp && !is_operator(temp->var))
	{
		leaf->cmd[i++] = ft_strdup(temp->var);
		temp = temp->next;
		if (temp)
			remove_current_tok(temp->prev, shell->user_command);
	}
	shell->tree->map = leaf;
	return (leaf);
}

t_tree	*create_left_branches(t_shell *shell, t_tok *temp)
{
	int	parentheses;

	parentheses = 0;
	temp = shell->user_command->start;
	while (temp)
	{
		if (temp && ft_strncmp(temp->var, "(", 2) == 0)
		{
			remove_front_tok(shell->user_command);
			parentheses++;
			temp = shell->user_command->start;
		}
		create_ending_leaf(shell, temp);
		create_op_left_dad_leaf(shell, temp, shell->tree->map);
		create_right_leaf
	}
	return (shell->tree);
}

t_tree	*create_op_left_dad_leaf(t_shell *shell, t_tok *temp, t_branch *map)
{
	t_branch	*leaf;

	leaf = malloc(sizeof(t_branch));
	if (!leaf)
		return (0);
	leaf->right = NULL;
	leaf->left = map;
	leaf->cmd = malloc(sizeof(char *) * 100);
	if (!leaf->cmd)
		return (0);
	leaf->cmd[0] = ft_strdup(temp->var);
	temp = temp->next;
	remove_current_tok(temp->prev, shell->user_command);
	leaf->cmd[1] = NULL;
	map = leaf;
	return (shell->tree);
}

t_tree	*create_left_branches(t_shell *shell, t_tok *temp)
{
	int	parentheses = 0;
	int	count;
	int	diff;

	fill_tree_with_operator(shell, temp);
	temp = go_to_first_and_or(shell->user_command);
	fill_tree_with_pipes(shell, temp);
	temp = go_to_first_operator(shell->user_command);
	temp->prio = 1;
	if (temp && temp->prev)
		temp = temp->prev;
	if (temp && ft_strncmp(temp->var, ")", 2) == 0)
	{
		parentheses = reverse_number_of_parentheses(temp);
		while (parentheses > 0)
		{
			count = 0;
			diff = 0;
			while (temp && ft_strncmp(temp->var, ")", 2) != 0)
				temp = temp->prev;
			temp = temp->prev;
			remove_current_tok(temp->next, shell->user_command);
			temp = go_to_last_opened_parenthese(temp, &count, &diff);
			remove_current_tok(temp, shell->user_command);
			parentheses--;
			/*t_tok	*tst = shell->user_command->start;
			int	i = 0;
			while (tst)
			{
				printf("command[%d] = %s\n", i, tst->var);
				tst = tst->next;
				i++;
			}
			*/
			temp = shell->user_command->start;
			while (temp && temp->prio != 1)
				temp = temp->next;
			fill_tree_with_operator(shell, temp);
			temp = shell->user_command->start;
			while (temp && temp->prio != 1)
				temp = temp->next;
			temp = temp->prev;
			fill_tree_with_pipes(shell, temp);
			while (temp && temp->prio != 1)
				temp = temp->next;
		}
		temp = shell->user_command->start;
		printf("coucou1\n");
		create_cmd_l_leaf(shell->tree, temp);
		printf("coucou2\n");
	}
	return (shell->tree);
}

t_tree	*create_cmd_l_leaf(t_tree *tree, t_tok *temp)
{
	t_branch	*leaf;
	t_branch	*travel;
	int			i;
	
	leaf = malloc(sizeof(t_branch));
	if (!leaf)
		return (0);
	leaf->right = NULL;
	leaf->left = NULL;
	i = 0;
	printf("temp is %s\n", temp->var);
	while (temp && !is_operator(temp->var))
	{
		temp = temp->next;
		i++;
	}
	leaf->cmd = malloc(sizeof(char *) * (i + 2));
	if (!leaf->cmd)
		return (0);
	i = 0;
	while (temp && !is_operator(temp->var))
	{
		leaf->cmd[i] = ft_strdup(temp->var);
		temp = temp->next;
		i++;
	}
	leaf->cmd[i] = NULL;
	travel = tree->start;
	while (travel && travel->left)
		travel = travel->left;
	travel->left = leaf;
	leaf->dad = travel;
	tree->map = leaf;
	return (tree);	
}
/*
t_tree	*create_right_branches(t_tree *tree, t_toklst *user_command, t_tok *temp)
{
	return (tree);
}
*/

t_tree	*create_ast_branches(t_tree *tree, t_shell *shell, t_tok *temp)
{
	create_left_branches(shell, temp);
	//create_right_branches(tree, user_command, temp);
	return (tree);
}

t_tree	*create_start_branch(t_tree *tree, t_tok *temp)
{
	t_branch	*branch;

	tree->nb_elem = 0;
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
	tree->start = branch;
	tree->nb_elem++;
	return (tree);
}

/*
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
*/