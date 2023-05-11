/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:26:05 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 14:37:17 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exit_overflow(char *str)
{
	if (str && ft_strlen(str) > 20)
		return (EXIT_FAILURE);
	if (str && ft_strlen(str) < 19)
		return (EXIT_SUCCESS);
	if (str[0] == '-')
	{
		if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
			return (EXIT_FAILURE);
	}
	else
	{
		if (ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exit_b_shell(t_shell *shell, char **command, int pipe)
{
	if (pipe)
		return (EXIT_SUCCESS);
	if ((command[1] && !ft_strisdigit(command[1]))
		|| (command[1] && ft_strisdigit(command[1])
			&& exit_overflow(command[1])))
	{
		printf("exit: %s: numeric argument required\n", command[1]);
		g_err = 255;
	}
	else if (command[1] && ft_strisdigit(command[1]))
	{
		if (command[2])
		{
			g_err = 1;
			return (printf("exit: too many arguments\n"));
		}
		g_err = ft_atoi(command[1]);
	}
	clear_toklst(shell->user_command);
	clean_memory(shell);
	printf(YEL "Exit Minishell\n" WHT);
	exit(g_err);
	return (EXIT_SUCCESS);
}
