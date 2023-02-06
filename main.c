/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:46:31 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/06 19:30:53 by eleleux          ###   ########.fr       */
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

int	is_builtin_command(t_shell *shell)
{
		
	if (ft_strncmp(shell->user_command->start->var, "pwd", 4) == 0
		|| ft_strncmp(shell->user_command->start->var, "cd", 3) == 0
		|| ft_strncmp(shell->user_command->start->var, "export", 7) == 0
		|| ft_strncmp(shell->user_command->start->var, "env", 4) == 0
		|| ft_strncmp(shell->user_command->start->var, "unset", 6) == 0
		|| ft_strncmp(shell->user_command->start->var, "exit", 5) == 0
		|| ft_strncmp(shell->user_command->start->var, "echo", 5) == 0)
			return (TRUE);
	return (FALSE);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_shell	shell;

	if (ac != 1)
		return (printf("Minishell is pure, no arguments please\n"));
	allocate_shell(&shell, envp);
	printf(YEL "Open Minishell\n" WHT);
	while (ft_strncmp(shell.line_readed, "exit", 5))
	{
		readline_manager(&shell);
		if (!shell.line_readed)
			break ;
		if (shell.line_readed[0] != '\0')
		{
			token_parsing(shell.user_command, shell.line_readed);
			tokenisation(shell.user_command, shell.sorted_env_l);
			if (is_builtin_command(&shell))
				execute_builtin_cmd(&shell);
			else
			{
				pipe_command(&shell);
				//printf("%d\n", shell.user_command->nb_elem);
				clean_between_cmds(&shell);
			}
			//	command_manager(&shell, envp);
		}
	}
	clean_memory(&shell);
	return (0);
}
