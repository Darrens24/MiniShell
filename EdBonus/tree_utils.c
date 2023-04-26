/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:54:54 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/26 16:19:20 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_toklst	*split_right(t_toklst *active_command)
{
	t_toklst	*new_right_list;
	t_tok		*temp;

	new_right_list = malloc(sizeof(t_toklst));
	if (!new_right_list)
		return (0);
	new_right_list->nb_elem = 0;
	temp = go_to_branch_start(active_command);
	if (temp && is_operator(temp->var))
		temp = temp->next;
	while (temp)
	{
		new_back_tok(new_right_list, temp->var, 0, ft_strlen(temp->var));
		temp = temp->next;
	}
	return (new_right_list);
}

t_toklst	*split_left(t_toklst *active_command)
{
	t_toklst	*new_left_list;
	t_tok		*temp;

	new_left_list = malloc(sizeof(t_toklst));
	if (!new_left_list)
		return (0);
	new_left_list->nb_elem = 0;
	temp = go_to_branch_start(active_command);
	if (temp && is_operator(temp->var))
		temp = temp->prev;
	while (temp)
	{
		new_front_tok(new_left_list, temp->var);
		temp = temp->prev;
	}
	return (new_left_list);
}

char	**allocate_operator_cmd(t_tok *temp)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 2);
	if (!cmd)
		return (0);
	cmd[0] = ft_strdup(temp->var);
	cmd[1] = NULL;
	return (cmd);
}

char	**allocate_classic_cmd(t_tok *temp)
{
	char	**cmd;
	t_tok	*start;
	int		i;

	i = 0;
	start = temp;
	while (start)
	{
		start = start->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (0);
	i = 0;
	while (temp)
	{
		cmd[i] = ft_strdup(temp->var);
		temp = temp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**give_active_command(t_toklst *left_command)
{
	t_tok		*temp;
	char		**cmd;
	int			i;

	i = 0;
	/*
	temp = left_command->start;
	while (temp)
	{
		printf("left_command is %s\n", temp->var);
		temp = temp->next;
	}

	*/
	if (operator_in_cmd(left_command))
	{
		temp = go_to_branch_start(left_command);
		cmd = allocate_operator_cmd(temp);
	}
	else if (left_command)
	{
		cmd = allocate_classic_cmd(left_command->start);
	}
	else
		cmd = NULL;
	return (cmd);
}