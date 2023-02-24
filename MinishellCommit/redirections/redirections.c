/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:05:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/24 10:56:18 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_redirection(t_shell *shell, t_tok *temp)
{
	shell->infile = open(temp->next->var, O_RDONLY);
	delete_operator_and_infile(shell);
	if (shell->infile < 0)
		return (printf("Infile opening failed\n"));
	if (shell->user_command->nb_elem != 0
		&& !is_infile_redirection(shell->user_command))
		dup2(shell->infile, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int	heredoc_redirection(t_shell *shell, t_tok *temp)
{
	shell->limiter_doc = ft_strdup(temp->next->var);
	if (pipe(shell->doc_fd) < 0)
		return (printf("DocPipe failed\n"));
	delete_operator_and_infile(shell);
	while (1)
	{
		shell->buffer_doc = readline("here_doc >> ");
		if (!shell->buffer_doc || ft_strncmp(shell->buffer_doc,
				shell->limiter_doc, ft_strlen(shell->limiter_doc) + 1) == 0)
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
	if (!is_infile_redirection(shell->user_command))
		heredoc_dup(shell);
	return (EXIT_SUCCESS);
}

int	heredoc_dup(t_shell *shell)
{
	close(shell->doc_fd[1]);
	shell->saved_stdin = dup(STDIN_FILENO);
	dup2(shell->doc_fd[0], STDIN_FILENO);
	close(shell->doc_fd[0]);
	return (EXIT_SUCCESS);
}

int	outfile_redirection(t_shell *shell, t_tok *temp)
{
	shell->outfile = open(temp->next->var, O_CREAT | O_RDWR | O_TRUNC, 0644);
	delete_operator_and_outfile(shell);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	if (!is_outfile_redirection(shell->user_command))
		shell->out = true;
	return (EXIT_SUCCESS);
}

int	append_redirection(t_shell *shell, t_tok *temp)
{
	shell->outfile = open(temp->next->var, O_CREAT | O_RDWR | O_APPEND, 0644);
	delete_operator_and_outfile(shell);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	if (!is_outfile_redirection(shell->user_command))
		shell->out = true;
	return (EXIT_SUCCESS);
}
