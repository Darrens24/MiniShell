/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:17:35 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/25 11:06:23 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pids_fds(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < (get_number_of_commands(shell) - 1))
		free(shell->fd[i]);
	free(shell->fd);
	free(shell->pid);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (EXIT_SUCCESS);
}

int	free_increment(t_increment *incr)
{
	free(incr->sh_level);
	free(incr->itoa_sh);
	free(incr->new_sh_level);
	free(incr);
	return (EXIT_SUCCESS);
}

int	clean_between_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->multi_cmd)
	{
		while (i < get_number_of_commands(shell) && shell->multi_cmd)
		{
			free_array(shell->multi_cmd[i]);
			i++;
		}
		free(shell->multi_cmd);
	}
	free_array(shell->array_env);
	free(shell->home);
	free_pids_fds(shell);
	return (EXIT_SUCCESS);
}

int	clean_memory(t_shell *shell)
{
	free(shell->line_readed);
	clear_chained_lst(shell->env_l);
	clear_chained_lst(shell->sorted_env_l);
	free(shell->env_l);
	free(shell->sorted_env_l);
	free(shell->user_command);
	free_array(shell->ls_cmd);
	return (EXIT_SUCCESS);
}
