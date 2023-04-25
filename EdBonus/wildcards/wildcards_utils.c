/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:11:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/19 16:22:50 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	jump_next_wildcard(char *str, int index)
{
	while (str[index] && str[index] != '*')
		index++;
	return (index);
}

int	jump_previous_wildcard(char *str, int index)
{
	while (str[index] && str[index] != '*')
		index--;
	index++;
	return (index);
}

char	*remove_newline_from_buffer(char *buffer)
{
	char	*buffer_without_newline;

	if (buffer && strchr(buffer, '\n'))
	{
		buffer_without_newline = ft_strndup(buffer, 0, ft_strlen(buffer) - 1);
		free(buffer);
		return (buffer_without_newline);
	}
	return (buffer);
}

int	execute_ls_in_tmp(t_shell *shell, char **envp)
{
	pid_t	pid;
	int		fd_temp;

	fd_temp = open(".tmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_temp < 0)
		return (printf("Temp opening failed\n"));
	shell->saved_stdout = dup(STDOUT_FILENO);
	pid = fork();
	if (pid < 0)
		return (printf("Wildcard fork failed\n"));
	if (pid == 0)
	{
		dup2(fd_temp, STDOUT_FILENO);
		execve("/bin/ls", shell->ls_cmd, envp);
	}
	waitpid(pid, 0, 0);
	dup2(STDOUT_FILENO, shell->saved_stdout);
	close(fd_temp);
	return (EXIT_SUCCESS);
}

void	add_files_to_toklist(char *buffer, int fd_temp, t_shell *shell)
{
	while (buffer)
	{	
		free(buffer);
		buffer = get_next_line(fd_temp);
		if (!buffer)
			break ;
		buffer = remove_newline_from_buffer(buffer);
		if (is_matching_file(buffer, shell))
		{
			new_wildcard_tok(shell->user_command, buffer);
			shell->nb_of_sub++;
		}
	}
}
