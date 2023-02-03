/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:05:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/03 10:55:21 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	is_redirection(t_toklst *user_command)
{
	if ((ft_strncmp(user_command->start->var, "<", 2) == 0)
		|| (ft_strncmp(user_command->start->var, "<<", 3) == 0)
		|| (ft_strncmp(user_command->end->prev->var, ">", 2) == 0)
		|| (ft_strncmp(user_command->end->prev->var, ">>", 2) == 0))
			return (TRUE);
	return (FALSE);
}

int	redirection_parsing(t_shell *shell)
{
	if (ft_strncmp(shell->user_command->start->var, "<", 2) == 0)
		infile_redirection(shell);
	else if (ft_strncmp(shell->user_command->start->var, "<<", 3) == 0)
		heredoc_redirection(shell);
	if (ft_strncmp(shell->user_command->end->prev->var, ">", 2) == 0)
		outfile_redirection(shell);
	else if (ft_strncmp(shell->user_command->end->prev->var, ">>", 3) == 0)
		append_redirection(shell);
	return (EXIT_SUCCESS);
}

int	outfile_redirection(t_shell *shell)
{
	
}

int	delete_operator_and_infile(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < 2)
		remove_front_tok(shell->user_command);
	return (EXIT_SUCCESS);
}

int	infile_redirection(t_shell *shell)
{
	shell->infile = open(shell->user_command->start->var, O_RDONLY);
	if (shell->infile < 0)
		return (printf("Infile opening failed\n"));
	if (access(shell->user_command->start->var, F_OK, R_OK) < 0)
		return (perror("Infile permissions denied\n"));
	delete_operator_and_infile(shell);
	dup2(shell->infile, STDIN_FILENO);
	//close(shell->infile);
	
}

char	*append_newline(char *limiter)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(limiter) + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (limiter[i])
	{
		result[i] = limiter[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
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

int	outfile_redirection(t_shell *shell)
{

}

int	append_redirection(t_shell *shell)
{
}*/
