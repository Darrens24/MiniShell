/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:02:40 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/28 10:31:23 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_pwd(t_shell *shell, t_chained *list)
{
	char	*pwd;
	t_node	*temp;
	int		index;

	pwd = ft_strjoin("PWD=", shell->current_dir_path);
	temp = list->start;
	index = 0;
	while (temp)
	{
		if (ft_strncmp("PWD=", temp->variable, 4) == 0)
		{
			remove_current_node(temp, list);
			new_current_node(list, index, pwd);
			free(pwd);
			return (EXIT_SUCCESS);
		}
		index++;
		temp = temp->next;
	}
	new_back_node(list, pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

int	update_oldpwd(t_shell *shell, t_chained *list)
{
	char	*oldpwd;
	t_node	*temp;
	int		index;

	oldpwd = ft_strjoin("OLDPWD=", shell->previous_dir_path);
	temp = list->start;
	index = 0;
	while (temp)
	{
		if (ft_strncmp("OLDPWD=", temp->variable, 7) == 0)
		{
			remove_current_node(temp, list);
			new_current_node(list, index, oldpwd);
			free(oldpwd);
			return (EXIT_SUCCESS);
		}
		index++;
		temp = temp->next;
	}
	new_back_node(list, oldpwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}
