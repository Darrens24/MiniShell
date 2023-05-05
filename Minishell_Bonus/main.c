/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:51:51 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/05 16:19:04 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	is_parenthese(char *str)
{
	if (ft_strncmp(str, "(", 2) == 0 || ft_strncmp(str, ")", 2) == 0)
		return (TRUE);
	return (FALSE);
}

int	bonus_errors(t_shell *shell)
{
	t_tok	*tempstart;
	t_tok	*tempend;
	int		open_par;
	int		count;
	int		diff;

 	tempstart = shell->user_command->start;
 	tempend = shell->user_command->end;
 	open_par = 0;
	count = 0;
	diff = 0;
 	if ((is_operator(tempstart->var) && tempstart->quote == 0) || (is_operator(tempend->var) && tempend->quote == 0))
 		return (printf("Invalid syntax1\n"));
 	while (tempstart)
	{
		if (!is_operator(tempstart->var) && !is_parenthese(tempstart->var) && tempstart->next && !ft_strncmp(tempstart->next->var, "(", 2))
			return (printf("Invalid syntax2\n"));
		else if (!ft_strncmp(tempstart->var, ")", 2) && tempstart->next && !is_operator(tempstart->next->var) && ft_strncmp(tempstart->next->var, ")", 2))
			return (printf("Invalid syntax3\n"));
		else if (!ft_strncmp(tempstart->var, "(", 2) && tempstart->next && !ft_strncmp(tempstart->next->var, ")", 2))
			return (printf("Invalid syntax4\n"));
		tempstart = tempstart->next;
	}
 	tempstart = shell->user_command->start;
 	while (tempstart)
 	{
 		if (tempstart && !ft_strncmp(tempstart->var, ")", 2) && open_par == 0)
			return (printf("Invalid syntax5\n"));
 		if (tempstart && !ft_strncmp(tempstart->var, "(", 2))
 		{
 			open_par++;
 			if (number_of_parentheses(tempstart) < 0)
 				return (EXIT_FAILURE);
			count = number_of_parentheses(tempstart);
 			tempstart = go_to_first_closed_parenthese(tempstart, &count, &diff);
 			tempstart = go_to_last_closed_parenthese(tempstart, &count, &diff);
			open_par--;
 		}
		else
			tempstart = tempstart->next;
 	}
 	return (EXIT_SUCCESS);
} 

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
				t_tok	*temp = shell.user_command->start;
				parse_wildcard(&shell, envp, temp);
				if ((shell.user_command->nb_elem != 0)
					&& (infile_redirection_parsing(&shell) != 0
						|| outfile_redirection_parsing(&shell) != 0))
					good = FALSE;
				//if (good == TRUE && operator_in_cmd(shell.user_command))
				shell.nb_of_fds_to_malloc = 0;
				shell.bcmd = get_bcmd(shell.user_command, &shell);
				printf("cc\n");
				fill_trinary_tree(shell.user_command, &shell);
				execution_bonus(&shell, shell.tree->map);
				free_array(shell.tree->start->cmd);
				shell.tree->start->cmd = NULL;
				free(shell.tree->start);
				shell.tree->start = NULL;
				free(shell.tree);
				shell.tree = NULL;
				reinitializer(&shell);
				//else if (good == TRUE)
					//pipe_command(&shell);
				clean_between_cmds(&shell);
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
