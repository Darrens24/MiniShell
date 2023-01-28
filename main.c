/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:46:31 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/27 18:22:28 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	shell;

	//shell = malloc(sizeof(t_shell));
	allocate_shell(&shell, envp);
	while (ft_strncmp(shell.line_readed, "exit", 5))
	{
		free(shell.line_readed);
		shell.line_readed = readline(MAG "Minishell >> " WHT);
		if (!shell.line_readed)
			return (EXIT_FAILURE);
		add_history(shell.line_readed);
		if (execute_directory_cmd(&shell) == TRUE)
			execute_directory_cmd(&shell);
		else if (execute_env_cmd(&shell) == TRUE)
			execute_env_cmd(&shell);
	}
	clean_memory(&shell);
	return (0);
}
