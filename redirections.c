
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:05:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/14 17:41:59 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirection_parsing(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp && is_infile_redirection(shell->user_command))
	{
		if (ft_strncmp(temp->var, "<", 2) == 0)
		{
			if (!temp->next)
				return (printf("Redirection needs a file\n"));
			if (infile_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else if (ft_strncmp(temp->var, "<<", 3) == 0)
		{
			if (!temp->next)
				return (printf("Heredoc needs a delimiter\n"));
			if (heredoc_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else
			temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	infile_redirection(t_shell *shell, t_tok *temp)
{
	close(shell->infile);
	shell->infile = open(temp->next->var, O_RDONLY);
	delete_operator_and_infile(shell);
	if (shell->infile < 0)
		return (printf("Infile opening failed\n"));
	if (shell->user_command->nb_elem != 0 && !is_infile_redirection(shell->user_command))
	{
		shell->saved_stdin = dup(STDIN_FILENO);
		dup2(shell->infile, STDIN_FILENO);
	}
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

int	outfile_redirection_parsing(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp && is_outfile_redirection(shell->user_command))
	{
		if (ft_strncmp(temp->var, ">", 2) == 0)
		{
			if (!temp->next)
				return (printf("Redirection needs a file\n"));
			if (outfile_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else if (ft_strncmp(temp->var, ">>", 3) == 0)
		{
			if (!temp->next)
				return (printf("Append needs a file\n"));
			if (append_redirection(shell, temp) != 0)
				return (EXIT_FAILURE);
			temp = shell->user_command->start;
		}
		else
			temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	outfile_redirection(t_shell *shell, t_tok *temp)
{
	close(shell->outfile);
	shell->outfile = open(temp->next->var, O_CREAT | O_RDWR | O_TRUNC, 0644);
	delete_operator_and_outfile(shell);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	/*if (access(shell->outfile, R_OK | W_OK) < 0)
		return (printf("Outfile permissions denied\n"));*/
	if (!is_outfile_redirection(shell->user_command))
	{
		shell->saved_stdout = dup(STDOUT_FILENO);
		shell->out = true;
	}
	return (EXIT_SUCCESS);
}

int	append_redirection(t_shell *shell, t_tok *temp)
{
	close(shell->outfile);
	shell->outfile = open(temp->next->var, O_CREAT | O_RDWR | O_APPEND, 0644);
	delete_operator_and_outfile(shell);
	if (shell->outfile < 0)
		return (printf("Outfile opening failed\n"));
	if (!is_outfile_redirection(shell->user_command))
	{
		shell->saved_stdout = dup(STDOUT_FILENO);
		shell->out = true;
	}
	return (EXIT_SUCCESS);
}

