/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:11:29 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/25 15:54:15 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_branch	*clean(t_branch *temp)
{
	if (temp && temp->left)
		return (clean(temp->left));
	else if (temp && temp->right)
		return (clean(temp->right));
	else if (temp && temp->dad)
	{
		free_array(temp->cmd);
		temp->left = NULL;
		temp->right = NULL;
		temp->left_command = NULL;
		temp->right_command = NULL;
		return (clean(temp->dad));
	}
	return (temp);
}
