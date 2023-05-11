/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:51:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/11 13:27:11 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	readline_manager(t_shell *shell)
{
	free(shell->line_readed);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	remove_ctrlc(1);
	shell->line_readed = readline("Minishell >> ");
	remove_ctrlc(0);
	if (!shell->line_readed)
		return (EXIT_FAILURE);
	if (shell->line_readed && *shell->line_readed)
		add_history(shell->line_readed);
	return (EXIT_SUCCESS);
}

void	reinitializer(t_shell *shell)
{
	shell->nb_of_pipes = 0;
	shell->index_of_pipes = 0;
	shell->last_index = -1;
	shell->index_of_commands = 0;
	shell->index_of_pid = 0;
	shell->valid_pipe = 0;
}

static void	execute_user_command(t_shell *shell, int good, char **envp)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	parse_wildcard(shell, envp, temp);
	if ((shell->user_command->nb_elem != 0)
		&& (infile_redirection_parsing(shell) != 0
			|| outfile_redirection_parsing(shell) != 0))
		good = FALSE;
	if (good == TRUE)
	{
		shell->nb_of_fds_to_malloc = 0;
		shell->bcmd = get_bcmd(shell->user_command, shell);
		fill_trinary_tree(shell->user_command, shell);
		execution_bonus(shell, shell->tree->map);
		free_array(shell->tree->start->cmd);
		shell->tree->start->cmd = NULL;
		free(shell->tree->start);
		shell->tree->start = NULL;
		free(shell->tree);
		shell->tree = NULL;
		reinitializer(shell);
		clean_between_cmds(shell);
	}
	clear_toklst(shell->user_command);
}

static void	check_and_execute(t_shell *shell, int good, char **envp)
{
	token_parsing(shell->user_command, shell->line_readed);
	if (shell->user_command->nb_elem && token_checker(shell))
	{
		printf("Minishell: syntax error\n");
		clear_toklst(shell->user_command);
	}
	if (shell->user_command->nb_elem)
	{
		tokenisation(shell->user_command, shell->sorted_env_l);
		if (bonus_errors(shell))
			clear_toklst(shell->user_command);
		else
			execute_user_command(shell, good, envp);
	}
	dup2(shell->saved_stdin, STDIN_FILENO);
	dup2(shell->saved_stdout, STDOUT_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	int		good;
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (printf("Minishell is pure, no arguments please\n"));
	allocate_shell(&shell, envp);
	printf(YEL "Open Minishell\n" WHT);
	while (1)
	{
		good = TRUE;
		readline_manager(&shell);
		if (!shell.line_readed)
		{
			printf(YEL "\033[AMinishell >> Exit Minishell\n" WHT);
			break ;
		}
		if (*shell.line_readed)
			check_and_execute(&shell, good, envp);
	}
	clean_memory(&shell);
	system("leaks minishell");
	return (0);
}
