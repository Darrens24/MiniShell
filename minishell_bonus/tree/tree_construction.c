/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_construction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:51:18 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 18:29:49 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clear_splitted_cmd(t_branch *map, char mode)
{
	if (mode == 'l')
	{
		clear_toklst(map->left_command);
		free(map->left_command);
		map->left_command = NULL;
	}
	else if (mode == 'r')
	{
		clear_toklst(map->right_command);
		free(map->right_command);
		map->right_command = NULL;
	}
}

t_tree	*get_new_start_split_command(t_shell *shell, t_branch *map)
{
	if (map && map->left_command)
	{
		create_left_leaf(map);
		if (map->left->cmd_block > 0)
			map->left->subshell = ft_tklstcpy(map->left_command);
		clear_splitted_cmd(map, 'l');
		if (map->left->cmd_block == 0)
			map = map->left;
		get_new_start_split_command(shell, map);
	}
	else if (map && map->right_command)
	{
		create_right_leaf(map);
		if (map->right->cmd_block > 0)
			map->right->subshell = ft_tklstcpy(map->right_command);
		clear_splitted_cmd(map, 'r');
		if (map->right->cmd_block == 0)
			map = map->right;
		get_new_start_split_command(shell, map);
	}
	else if (map && map->dad)
		get_new_start_split_command(shell, map->dad);
	return (shell->tree);
}
