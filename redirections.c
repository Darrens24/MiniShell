
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:05:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/07 15:47:06 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirection_parsing(t_shell *shell)
{
	if (shell->user_command->start && ft_strncmp(shell->user_command->start->var, "<", 2) == 0)
		return (infile_redirection(shell));
	else if (shell->user_command->start && ft_strncmp(shell->user_command->start->var, "<<", 3) == 0)
		return (heredoc_redirection(shell));
	return (EXIT_SUCCESS);
}

int	outfile_redirection_parsing(t_shell *shell)
{
	if (shell->user_command->end->prev && ft_strncmp(shell->user_command->end->prev->var, ">", 2) == 0)
		return (outfile_redirection(shell));
	else if (shell->user_command->end->prev && ft_strncmp(shell->user_command->end->prev->var, ">>", 3) == 0)
		return (append_redirection(shell));
	return (EXIT_SUCCESS);
}

int	outfile_redirection(t_shell *shell)
{
	if (access(shell->user_command->end->var, R_OK | W_OK) < 0)
		return (printf("Outfile permissions denied\n"));
	close(shell->outfile);
	shell->outfile = open(shell->user_command->end->var, O_CREAT | O_RDWR | O_TRUNC, 0644);
	delete_operator_and_outfile(shell);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	shell->out = TRUE;
	shell->saved_stdout = dup(STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	append_redirection(t_shell *shell)
{
	if (access(shell->user_command->end->var, R_OK | W_OK) < 0)
		return (printf("Outfile permissions denied\n"));
	close(shell->outfile);
	shell->outfile = open(shell->user_command->end->var, O_CREAT | O_RDWR | O_APPEND, 0644);
	delete_operator_and_outfile(shell);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	shell->out = TRUE;
	dup2(shell->outfile, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	infile_redirection(t_shell *shell)
{
	close(shell->infile);
	shell->infile = open(shell->user_command->start->next->var, O_RDONLY);
	delete_operator_and_infile(shell);
	if (shell->infile < 0)
		return (printf("Infile opening failed\n"));
	shell->saved_stdin = dup(STDIN_FILENO);
	dup2(shell->infile, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int	heredoc_redirection(t_shell *shell)
{
	shell->limiter_doc = ft_strdup(shell->user_command->start->next->var);
	if (pipe(shell->doc_fd) < 0)
		return (printf("DocPipe failed\n"));
	delete_operator_and_infile(shell);
	while (1)
	{
		shell->buffer_doc = readline(CYN "here_doc >> " WHT);
		if (!shell->buffer_doc || ft_strncmp(shell->buffer_doc, shell->limiter_doc, ft_strlen(shell->limiter_doc) + 1) == 0)
		{
			if (!shell->buffer_doc)
				ft_putchar_fd('\n', STDOUT_FILENO);
			break ;
		}
		ft_putstr_fd(shell->buffer_doc, shell->doc_fd[1]);
		ft_putchar_fd('\n', shell->doc_fd[1]);
		free(shell->buffer_doc);
	}
	free(shell->buffer_doc);
	free(shell->limiter_doc);
	close(shell->doc_fd[1]);
	shell->saved_stdin = dup(STDIN_FILENO);
	dup2(shell->doc_fd[0], STDIN_FILENO);
	close(shell->doc_fd[0]);
	return (EXIT_SUCCESS);
}
