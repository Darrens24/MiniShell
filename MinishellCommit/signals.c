/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:13:53 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/07 17:09:41 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int num)
{
/*	struct termios term;

	tcgetattr(STDIN_FILENO, &new);
	term.c_iflag |= IGNBRK;
	term.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
	term.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);*/
	struct termios	saved;
	struct termios	new;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ICANON | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	if (num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_err = 130;
	}
	else if (num == SIGQUIT)
		return ;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &saved);
}
