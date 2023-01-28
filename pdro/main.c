/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:46:31 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/28 14:49:43 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell		shell;
	t_toklst	toklst;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	allocate_shell(&shell, envp);
	while (shell.line_readed && ft_strncmp(shell.line_readed, "exit", 5))
	{
		free(shell.line_readed);
		shell.line_readed = readline(MAG "Minishell >> " WHT);
		parsing(&toklst, shell.line_readed);
		if (ft_strncmp(shell.line_readed, "pwd", 4) == 0)
			print_pwd_linux();
		print_toklst(&toklst);
		add_history(shell.line_readed);
		clear_toklst(&toklst);
	}
	return (0);
}
