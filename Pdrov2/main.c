	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2023/01/25 18:46:31 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/07 13:47:48 by pfaria-d         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#include "minishell.h"

int	readline_manager(t_shell *shell)
{
	free(shell->line_readed);
	shell->line_readed = readline(MAG "Minishell >> " WHT);
	if (!shell->line_readed)
		return (EXIT_FAILURE);
	if (shell->line_readed[0] != '\0')
		add_history(shell->line_readed);
	return (EXIT_SUCCESS);
}

int	is_builtin_command(t_shell *shell, int i)
{
		
	if (ft_strncmp(shell->multi_cmd[i][0], "pwd", 4) == 0
		|| ft_strncmp(shell->multi_cmd[i][0], "cd", 3) == 0
		|| ft_strncmp(shell->multi_cmd[i][0], "export", 7) == 0
		|| ft_strncmp(shell->multi_cmd[i][0], "env", 4) == 0
		|| ft_strncmp(shell->multi_cmd[i][0], "unset", 6) == 0
		|| ft_strncmp(shell->multi_cmd[i][0], "exit", 5) == 0
		|| ft_strncmp(shell->multi_cmd[i][0], "echo", 5) == 0)
			return (TRUE);
	return (FALSE);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	int	good;
	t_shell	shell;

	if (ac != 1)
		return (printf("Minishell is pure, no arguments please\n"));
	allocate_shell(&shell, envp);
	printf(YEL "Open Minishell\n" WHT);
	while (ft_strncmp(shell.line_readed, "exit", 5))
	{
		good = TRUE;
		readline_manager(&shell);
		if (!shell.line_readed)
			break ;
		if (shell.line_readed[0] != '\0')
		{
			token_parsing(shell.user_command, shell.line_readed);
			tokenisation(shell.user_command, shell.sorted_env_l);
			if (infile_redirection_parsing(&shell) != 0)
				good = FALSE;
			if (outfile_redirection_parsing(&shell) != 0)
				good = FALSE;
			if (good == TRUE)
				pipe_command(&shell);
			clean_between_cmds(&shell);
		}
	}
	clean_memory(&shell);
	return (0);
}
