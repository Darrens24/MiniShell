/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:23:45 by eleleux           #+#    #+#             */
/*   Updated: 2023/03/08 16:19:45 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(char **array_env)
{
	int	i;

	i = 0;
	while (array_env[i])
	{
		if (ft_strncmp(array_env[i], "HOME=", 5) == 0)
			return (array_env[i] + 5);
		i++;
	}
	return (NULL);
}

char	**get_command_in_tok(t_shell *shell, int index)
{
	char	**command;
	t_tok	*temp;
	int		nb_of_args;
	int		i;

	temp = NULL;
	temp = go_to_next_pipe(shell, temp, index);
	nb_of_args = 0;
	while (temp && temp->quote == 1)
	{
		temp = temp->next;
		nb_of_args++;
	}
	command = malloc(sizeof(char *) * (nb_of_args + 1));
	if (!command)
		return (NULL);
	temp = go_to_next_pipe(shell, temp, index);
	i = 0;
	while (temp && i < nb_of_args)
	{
		command[i++] = ft_strdup(temp->var);
		temp = temp->next;
	}
	command[i] = NULL;
	return (command);
}

int	get_number_of_pipes(t_shell *shell)
{
	t_tok	*temp;
	int		nb_of_cmd;

	nb_of_cmd = 0;
	temp = shell->user_command->start;
	while (temp)
	{
		if (ft_strncmp(temp->var, "|", 2) == 0 && temp->quote == 0)
			nb_of_cmd++;
		temp = temp->next;
	}
	return (nb_of_cmd);
}

int	get_array_cmd_and_pipe_fds(t_shell *shell)
{
	int		i;

	shell->pid = malloc(sizeof(int) * get_number_of_commands(shell));
	if (!shell->pid)
		return (EXIT_FAILURE);
	i = -1;
	shell->fd = malloc(sizeof(int *) * (get_number_of_pipes(shell)));
	if (!shell->fd)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < (get_number_of_pipes(shell)))
	{
		shell->fd[i] = malloc(sizeof(int) * 2);
		if (!shell->fd[i])
			return (EXIT_FAILURE);
	}
	shell->multi_cmd = malloc(sizeof(char *)
			* (get_number_of_commands(shell) + 1));
	if (!shell->multi_cmd)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < get_number_of_commands(shell))
		shell->multi_cmd[i] = get_command_in_tok(shell, i);
	shell->multi_cmd[i] = NULL;
	return (EXIT_SUCCESS);
}
