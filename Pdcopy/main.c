/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:51:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/04 18:40:48 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/* int	check_inside_block( */
/* int	bonus_errors(t_shell *shell) */
/* { */
/* 	t_tok	*tempstart; */
/* 	t_tok	*tempend; */
/* 	int		open_par; */

/* 	tempstart = shell->user_command->start; */
/* 	tempend = shell->user_command->end; */
/* 	open_par = 0; */
/* 	if (is_operator(tempstart->var) || is_operator(tempend->var)) */
/* 		return (printf("Invalid syntax\n")); */
/* 	while (tempstart) */
/* 	{ */
/* 		if (!ft_strncmp(tempstart->var, "(", 2)) */
/* 		{ */
/* 			open_par++; */
/* 			if (number_of_parentheses(tempstart) < 0) */
/* 				return (EXIT_FAILURE); */
/* 			else if (number_of_parentheses > 1) */
/* 				if (check_inside_block(tempstart) < 0) */
/* 					return (EXIT_FAILURE); */
/* 			tempstart = operator_jump_parentheses(tempstart); */
/* 		} */
/* 		else */
/* 			tempstart = tempstart->next; */	
/* 	} */
/* 	return (EXIT_SUCCESS); */
/* } */

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

int	is_builtin_command(t_shell *shell, int index)
{
	if (ft_strncmp(shell->multi_cmd[index][0], "pwd", 4) == 0
		|| ft_strncmp(shell->multi_cmd[index][0], "cd", 3) == 0
		|| ft_strncmp(shell->multi_cmd[index][0], "export", 7) == 0
		|| ft_strncmp(shell->multi_cmd[index][0], "env", 4) == 0
		|| ft_strncmp(shell->multi_cmd[index][0], "unset", 6) == 0
		|| ft_strncmp(shell->multi_cmd[index][0], "exit", 5) == 0
		|| ft_strncmp(shell->multi_cmd[index][0], "echo", 5) == 0)
		return (TRUE);
	return (FALSE);
}

void print_cmds_with_blocks(t_branch *node) {
    if (node == NULL) {
        return;
    }

    if (node->cmd != NULL) {
        fprintf(stderr, "Commands in block %d:\n", node->cmd_block);
        for (int i = 0; node->cmd[i] != NULL; i++) {
            fprintf(stderr, "\t%s\n", node->cmd[i]);
        }
    }

    print_cmds_with_blocks(node->left);
    print_cmds_with_blocks(node->right);
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
			ft_putchar_fd('\n', STDOUT_FILENO);
			break ;
		}
		if (*shell.line_readed)
		{
			token_parsing(shell.user_command, shell.line_readed);
			if (shell.user_command->nb_elem && token_checker(&shell))
			{
				printf("Minishell: syntax error\n");
				clear_toklst(shell.user_command);
			}
			if (shell.user_command->nb_elem)
			{
				tokenisation(shell.user_command, shell.sorted_env_l);
			//	parse_wildcard(&shell, envp);
				if ((shell.user_command->nb_elem != 0)
					&& (infile_redirection_parsing(&shell) != 0
						|| outfile_redirection_parsing(&shell) != 0))
					good = FALSE;
				if (good == TRUE && and_or_in_cmd(shell.user_command))
				{
					shell.nb_of_fds_to_malloc = 0;
					shell.bcmd = get_bcmd(shell.user_command, &shell);
					fill_trinary_tree(shell.user_command, &shell);
					/* print_cmds_with_blocks(shell.tree->start); */
					//printf("Error : %d\n", bonus_errors(&shell));
					execution_bonus(&shell, shell.tree->map);
					free_array(shell.tree->start->cmd);
					free(shell.tree->start);
					free(shell.tree);
					clean_between_cmds(&shell);
				}
				else if (good == TRUE)
					pipe_command(&shell);
				clear_toklst(shell.user_command);
				dup2(shell.saved_stdin, STDIN_FILENO);
				dup2(shell.saved_stdout, STDOUT_FILENO);
			}
		}
	}
	clean_memory(&shell);
	system("leaks minishell");
	printf(YEL "Exit Minishell\n" WHT);
	return (0);
}
