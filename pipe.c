/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/31 17:58:38 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_number_of_commands(t_shell *shell)
{
	t_tok	*temp;
	int		nb_of_cmd;

	nb_of_cmd = 1;
	temp = shell->user_command->start;
	while (temp)
	{
		if (ft_strncmp(temp->var, "|", 2) == 0)
			nb_of_cmd++;
		temp = temp->next;
	}
	return (nb_of_cmd);
}

char	**get_command_in_tok(t_shell *shell, int index)
{
	char	**command;
	t_tok	*temp;
	int		nb_of_args = 0;
	int		i = 0;

	temp = shell->user_command->start;
	while (temp && i < index)
	{
		while (temp && ft_strncmp(temp->var, "|", 2) != 0)
			temp = temp->next;
		if (temp->next)
			temp = temp->next;
		i++;
	}
	while (temp && ft_strncmp(temp->var, "|", 2) != 0)
	{
		temp = temp->next;
		nb_of_args++;
	}
	command = malloc(sizeof(char *) * (nb_of_args + 1));
	if (!command)
		return (NULL);
	i = 0;
	temp = shell->user_command->start;
	while (temp && i < index)
	{
		while (temp && ft_strncmp(temp->var, "|", 2) != 0)
			temp = temp->next;
		if (temp->next)
			temp = temp->next;
		i++;
	}
	i = 0;
	while (temp && i < nb_of_args)
	{
		command[i] = ft_strdup(temp->var);
		i++;
		temp = temp->next;
	}
	command[i] = NULL;
	return (command);
}

int	execupe_pipe_command(t_shell *shell, char **envp)
{
	char	***commands;
	int		i;
	(void)envp;

	commands = malloc(sizeof(char *) * (get_number_of_commands(shell) + 1));
	if (!commands)
		return (EXIT_FAILURE);
	i = 0;
	while (i < get_number_of_commands(shell))
	{
		commands[i] = get_command_in_tok(shell, i);
		i++;
	}
	commands[i] = NULL;
	i = 0;
	int	j = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			printf("arg[%d] : %s\n",i, commands[i][j]);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
