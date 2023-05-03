/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:13:53 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/03 16:00:00 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_ctrlc(int mode)
{
	struct termios	termi;

	tcgetattr(0, &termi);
	if (mode == 1)
		termi.c_lflag &= ~ECHOCTL;
	else
		termi.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &termi);
}

void	do_nothing(int num)
{
	if (num == SIGINT)
		return ;
	if (num == SIGQUIT)
		return ;
}

void	do_nothing_but_quit3(int num)
{
	if (num == SIGINT)
		return ;
	if (num == SIGQUIT)
	{
		printf("Quit: 3\n");
		return ;
	}
}

void	handler(int num)
{
	struct termios	saved;
	struct termios	new;

	tcgetattr(STDIN_FILENO, &saved);
	new = saved;
	new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	if (num == SIGINT)
	{
		if (g_err != 130)
		{
			rl_replace_line("", 0);
			ft_putchar_fd('\n', 1);
			rl_on_new_line();
			rl_redisplay();
		}
		g_err = 1;
	}
	if (num == SIGQUIT)
		return ;
}

void	heredoc_handler(int num)
{
	if (num == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		g_err = 1;
		exit(1);
	}
	if (num == SIGQUIT)
		return ;
}
