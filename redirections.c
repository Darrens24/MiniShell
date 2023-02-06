
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:05:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/06 15:50:53 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirection_parsing(t_shell *shell)
{
	if (ft_strncmp(shell->user_command->start->var, "<", 2) == 0)
		return (infile_redirection(shell));
	else if (ft_strncmp(shell->user_command->start->var, "<<", 3) == 0)
		return (heredoc_redirection(shell));
	return (EXIT_SUCCESS);
}

int	outfile_redirection_parsing(t_shell *shell)
{
	if (ft_strncmp(shell->user_command->end->prev->var, ">", 2) == 0)
		outfile_redirection(shell);
	else if (ft_strncmp(shell->user_command->end->prev->var, ">>", 3) == 0)
		append_redirection(shell);
	return (EXIT_SUCCESS);
}

int	outfile_redirection(t_shell *shell)
{
	shell->outfile = open(shell->user_command->end->var, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	if (access(shell->user_command->end->var, R_OK | W_OK) < 0)
		return (printf("Outfile permissions denied\n"));
	delete_operator_and_outfile(shell);
	dup2(shell->outfile, STDOUT_FILENO);
	return (shell->outfile);
}

int	append_redirection(t_shell *shell)
{
	shell->outfile = open(shell->user_command->end->var, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	if (access(shell->user_command->end->var, R_OK | W_OK) < 0)
		return (printf("Outfile permissions denied\n"));
	delete_operator_and_outfile(shell);
	dup2(shell->outfile, STDOUT_FILENO);
	return (shell->outfile);
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
	char	*buffer;
	char	*limiter;
	

	limiter = append_newline(shell->user_command->start->next->var);
	if (pipe(shell->doc_fd) < 0)
		return (printf("DocPipe failed\n"));
	close(shell->doc_fd[0]);
	while (1)
	{
		buffer = readline("here_doc >> ");
		if (!buffer || !ft_strncmp(buffer, limiter, ft_strlen(limiter) + 1))
			break ;
		ft_putstr_fd(buffer, shell->doc_fd[1]);
		ft_putchar_fd('\n', shell->doc_fd[1]);
		free(buffer);
	}
	close(shell->doc_fd[1]);
	free(buffer);
	free(limiter);
	delete_operator_and_infile(shell);
	return (shell->doc_fd[0]);
}
