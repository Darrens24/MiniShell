/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:30:35 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/04 18:18:59 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	varjumper(char *var, int i)
{
	if (!var[i] || is_wspace(var[i])
		|| var[i] == '\"' || var[i] == '\'')
		i += 0;
	else
	{
		while (var[i] && var[i] != '\'' && var[i] != '\"'
			&& (ft_isalnum(var[i]) || var[i] == '_'))
			i++;
	}
	return (i);
}

char	*varparser(char *var, int i, char *newvar, t_chained *env)
{
	int	start;

	if (!var[i] || is_wspace(var[i])
		|| var[i] == '\"' || var[i] == '\'')
			newvar = ft_strjoin(newvar, "$");
	else
	{
		start = i;
		while (var[i] && var[i] != '\'' && var[i] != '\"'
			&& (ft_isalnum(var[i]) || var[i] == '_'))
			i++;
		newvar = envfinder(ft_strndup(var, start, i), newvar, env);
	}
	return (newvar);
}

char	*replace_by_env(t_shell *shell, char *buffer)
{
	char	*newline;
	int		i;
	char	*tmp;

	i = 0;
	newline = NULL;
	while (buffer && buffer[i])
	{
		if (buffer[i] == '$')
		{
			newline = varparser(buffer, ++i, newline, shell->sorted_env_l);
			i = varjumper(buffer, i);
		}
		else
		{
			tmp = ft_strndup(buffer, i, i + 1);
			newline = ft_strjoin(newline, tmp);
			i++;
		}
	}
	free(buffer);
	return (newline);
}

int	heredoc_prompt(t_shell *shell)
{
	signal(SIGINT, &heredoc_handler);
	while (1)
	{
		remove_ctrlc(1);
		shell->buffer_doc = readline("here_doc >> ");
		remove_ctrlc(0);
		if (!shell->buffer_doc || ft_strncmp(shell->buffer_doc,
				shell->limiter_doc, ft_strlen(shell->limiter_doc) + 1) == 0)
		{
			printf("\033[Ahere_doc >> ");
			exit(0);
		}
		shell->buffer_doc = replace_by_env(shell, shell->buffer_doc);
		ft_putstr_fd(shell->buffer_doc, shell->doc_fd[1]);
		ft_putchar_fd('\n', shell->doc_fd[1]);
		free(shell->buffer_doc);
	}
	return (EXIT_SUCCESS);
}

int	heredoc_redirection(t_shell *shell, t_tok *temp)
{
	int	waitpid_return;
	int	error_code;

	waitpid_return = 0;
	error_code = 0;
	shell->limiter_doc = ft_strdup(temp->next->var);
	if (pipe(shell->doc_fd) < 0)
		return (printf("DocPipe failed\n"));
	delete_operator_and_infile(shell);
	shell->here = fork();
	signal(SIGINT, &do_nothing);
	signal(SIGQUIT, &do_nothing);
	if (shell->here == 0)
		heredoc_prompt(shell);
	waitpid_return = waitpid(shell->here, &error_code, 0);
	if (waitpid_return > 0)
		error_func(error_code);
	free(shell->limiter_doc);
	if (g_err == 1)
		return (EXIT_FAILURE);
	if (!is_infile_redirection(shell->user_command))
		heredoc_dup(shell);
	return (EXIT_SUCCESS);
}
