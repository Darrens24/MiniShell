/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/19 18:28:36 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_parentheses(t_tok *temp)
{
	int		count;
	int		diff;

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

int	reverse_number_of_parentheses(t_tok *temp)
{
	int		count;
	int		diff;

	count = 0;
	diff = 0;
	while (temp && ft_strncmp(temp->var, "(", 2) != 0)
	{
		if (temp && ft_strncmp(temp->var, ")", 2) == 0)
		{
			count++;
			diff++;
		}
		temp = temp->prev;
	}
	if (temp && ft_strncmp(temp->var, "(", 2) == 0)
	{
		diff--;
		temp = temp->prev;
	}
	while (temp && diff > 0)
	{
		if (temp && ft_strncmp(temp->var, ")", 2) == 0)
		{
			count++;
			diff++;
		}
		else if (temp && ft_strncmp(temp->var, "(", 2) == 0)
			diff--;
		temp = temp->prev;
	}
	return (count);
}
/*
void	create_left_branches(t_branch *tree_branch, t_toklst *user_command)
{
	t_tok		*temp;
	t_branch	*branch;
	int			pipes;

	branch = malloc(sizeof(t_branch));
	if (!branch)
		return ;
	branch->left = NULL;
	branch->middle = NULL;
	branch->right = NULL;
	temp = user_command->start;
	pipes = 0;
	while (temp && !is_and_or(temp->var))
	{
		if (ft_strncmp(temp->var, "|", 2) == 0)
			pipes++;
		temp = temp->next;
	}
	temp = user_command->start;
	while (pipes > 0)
	{

	}
	if (ft_strncmp(temp->var, "|", 2) == 0)
	{
		branch->cmd[0] = ft_strdup(temp->var);
		branch->cmd[1] = NULL;
	}
	else if (is_and_or(temp->var))
	{
		temp = user_command->start;
	}

	tree_branch->left = branch;
}
*/

void	fill_trinary_tree(t_toklst *user_command, t_shell *shell)
{
	t_tok		*temp;
	int			par;
	int			nb_of_op;

	shell->tree = malloc(sizeof(t_tree));
	if (!shell->tree)
		return ;
	temp = user_command->start;
	nb_of_op = 0;
	par = 0;
	if (!and_or_in_cmd(user_command))
	{
		shell->tree = create_start_branch(shell->tree, user_command);
		temp = user_command->start;
		while (temp)
		{
			create_middle_branch(shell->tree, user_command);
			temp = user_command->start;
		}
		return ;
	}
	else
	{
		while (temp)
		{
			if (temp && ft_strncmp(temp->var, "(", 2) == 0)
			{
				par = number_of_parentheses(temp);
				while (temp && par > 0)
				{
					if (temp && ft_strncmp(temp->var, ")", 2) == 0)
						par--;
					temp = temp->next;
				}
			}
			if (is_and_or(temp->var))
				nb_of_op++;
			temp = temp->next;
		}
		temp = user_command->end;
		while (temp)
		{
			if (temp && ft_strncmp(temp->var, ")", 2) == 0)
			{
				par = reverse_number_of_parentheses(temp);
				while (temp && par > 0)
				{
					if (temp && ft_strncmp(temp->var, "(", 2) == 0)
						par--;
					temp = temp->prev;
				}
			}
			if (is_and_or(temp->var))
			{
				shell->tree = op_create_start_branch(shell->tree, temp);
				printf("start is %s\n", shell->tree->start->cmd[0]);
				break ;
			}
			temp = temp->prev;
		}
		//create_branches(shell->tree, user_command, temp);
	}
}

t_tree	*op_create_start_branch(t_tree *tree, t_tok *temp)
{
	t_branch	*branch;

	tree->nb_elem = 0;
	branch = malloc(sizeof(t_branch));
	if (!branch)
		return (0);
	branch->left = NULL;
	branch->middle = NULL;
	branch->right = NULL;
	branch->cmd = malloc(sizeof(char *) * 30);
	if (!branch->cmd)
		return (0);
	branch->cmd[0] = ft_strdup(temp->var);
	branch->cmd[1] = NULL;
	tree->start = branch;
	tree->nb_elem++;
	return (tree);
}

t_tree	*create_start_branch(t_tree *tree, t_toklst *user_command)
{
	t_branch	*branch;

	tree->nb_elem = 0;
	branch = malloc(sizeof(t_branch));
	if (!branch)
		return (0);
	branch->left = NULL;
	branch->middle = NULL;
	branch->right = NULL;
	fill_tree_command_remove_tok(user_command, branch);
	tree->start = branch;
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

int	is_and_or(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0)
		return (1);
	return (0);
}

int	is_operator(char *str)
{
	if (ft_strncmp(str, "&&", 3) == 0
		|| ft_strncmp(str, "||", 3) == 0
		|| ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

int	and_or_in_cmd(t_toklst *user_command)
{
	t_tok	*temp;

	temp = user_command->start;
	while (temp)
	{
		if (is_and_or(temp->var))
			return (1);
		temp = temp->next;
	}
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
