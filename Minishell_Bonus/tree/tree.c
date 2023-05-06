/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:07:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/06 10:32:19 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_tok	*start_when_and_or(t_tok *temp)
{
	while (temp)
	{
		if (is_and_or(temp->var) && temp->quote == 0)
			break ;
		if (temp && ft_strncmp(temp->var, ")", 2) == 0 && temp->quote == 0)
			return (and_or_reverse_jump_parentheses(temp));
		temp = temp->prev;
	}
	return (temp);
}

static t_tok	*start_when_pipe(t_tok *temp)
{
	while (temp)
	{
		if (is_operator(temp->var) && temp->quote == 0)
			break ;
		if (temp && ft_strncmp(temp->var, ")", 2) == 0 && temp->quote == 0)
			return (pipe_reverse_jump_parentheses(temp));
		temp = temp->prev;
	}
	return (temp);
}

t_tok	*go_to_branch_start(t_toklst *user_command)
{
	t_tok	    *temp;
    static int  prio = 0;

	temp = user_command->end;
	if (temp && and_or_in_cmd_outside_parentheses(user_command))
    {
		temp = start_when_and_or(temp);
        if (prio)
            temp->prio = prio;
		prio = 0;
    }
	else if (temp && pipe_in_cmd_outside_parentheses(user_command))
    {
		temp = start_when_pipe(temp);
        if (prio)
            temp->prio = prio;
		prio = 0;
    }
	else if (temp && ft_strncmp(temp->var, ")", 2) == 0 && temp->quote == 0)
	{
		remove_front_tok(user_command);
		remove_back_tok(user_command);
        prio++;
		temp = go_to_branch_start(user_command);
	}
	return (temp);
}

//ls[0] &&[0] ((cat lol[2] ||[2] whoami[2]) |[1] grep a[1]) 

t_tree	*get_new_start_split_command(t_shell *shell, t_branch *map)
{
	if (map && map->left_command)
	{
		create_left_leaf(map);
		if (map->left->cmd_block > 0)
		{
			map->left->subshell = ft_tklstcpy(map->left_command);
			clear_toklst(map->left_command);
			free(map->left_command);
			map->left_command = NULL;
			get_new_start_split_command(shell, map);
		}
		else
		{
			clear_toklst(map->left_command);
			free(map->left_command);
			map->left_command = NULL;
			get_new_start_split_command(shell, map->left);
		}
	}
	else if (map && map->right_command)
	{
		create_right_leaf(map);
		if (map->right->cmd_block > 0)
		{
			map->right->subshell = ft_tklstcpy(map->right_command);
			clear_toklst(map->right_command);
			free(map->right_command);
			map->right_command = NULL;
			get_new_start_split_command(shell, map);
		}
		else
		{
			clear_toklst(map->right_command);
			free(map->right_command);
			map->right_command = NULL;
			get_new_start_split_command(shell, map->right);
		}
	}
	else if (map && map->dad)
		get_new_start_split_command(shell, map->dad);
	return (shell->tree);
}

void	fill_trinary_tree(t_toklst *user_command, t_shell *shell)
{
	t_tok		*temp;

	shell->tree = malloc(sizeof(t_tree));
	if (!shell->tree)
		return ;
	shell->array_env = get_array_env(shell);
	shell->home = ft_strdup(get_home(shell->array_env));
	temp = user_command->start;
    if (operator_in_cmd(user_command))
    {
        temp = go_to_branch_start(user_command);
        shell->tree = create_start_branch(shell->tree, temp, user_command);
        shell->tree = get_new_start_split_command(shell, shell->tree->map);
    }
    else
    {
        shell->tree = create_single_branch(shell->tree, user_command, temp);
    }
}
