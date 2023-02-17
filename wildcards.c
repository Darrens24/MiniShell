/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:53:45 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/17 09:48:16 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ls_in_tmp(t_shell *shell, char **envp)
{
	char	**ls_cmd;
	pid_t	pid;
	int		fd_temp;

	ls_cmd = malloc(sizeof(char *) * 2); // 2 car ls
	if (!ls_cmd)
		return (EXIT_FAILURE);
	ls_cmd[0] = "ls";
	ls_cmd[1] = NULL;
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
		execve("/bin/ls", ls_cmd, envp);
	}
	waitpid(pid, 0, 0);
	dup2(STDOUT_FILENO, shell->saved_stdout);
	close(fd_temp);
	while (cmd_has_wildcard(shell))
	{
		get_wildcard_files(shell);
	}
	//unlink(".tmp"); --> a la toute fin de la traduction des wildcards
	return (EXIT_SUCCESS);
}

int	get_nb_of_wildcard(char *var)
{
	int	nb_of_wildcard;
	int	i;

	nb_of_wildcard = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == '*' && var[i + 1] == '*')
		{
			printf("Wildcard only manage current directory\n");
			return (-1);
		}
		else if (var[i] == '*')
			nb_of_wildcard++;
		i++;
	}
	return (nb_of_wildcard);
}

/* before, ncmp sur la len de before
 * middle chr a partir de len de before + 1, depasse l'* et marche si pas de befor
 * after index a len de buffer - len de after puis ncmp sur la len de after
 * un seul passage et ajoute directement a user_command
 */

int	compare_after_wildcard(char *buffer, t_shell *shell)
{
	int	i;

	i = ft_strlen(buffer) - ft_strlen(shell->wild_after);
/*	printf("len = %d\n", i);
	printf("buffer + i = %s\n", buffer + i);
	printf("wildafter = %s\n", shell->wild_after);*/
	if (buffer + i && ft_strncmp(buffer + i, shell->wild_after, ft_strlen(shell->wild_after)) == 0)
		return (true);
	return (false);
}

int	compare_middle_wildcard(char *buffer, t_shell *shell)
{
	int	i;
	int	j;

	i = ft_strlen(shell->wild_before) + 1;
	j = 0;
	while (shell->wild_middle[j])
	{
		if (!ft_strnstr((buffer + i), shell->wild_middle[j], ft_strlen(buffer)))
			return (false);
		//while (!ft_strncmp(
		//i = ft_strnstr((buffer + i), shell->wild_middle[j], ft_strlen(buffer));
		j++;
	}
	return (true);
}

int	is_matching_file(char *buffer, t_shell *shell)
{
	if (shell->wild_before && shell->wild_middle && shell->wild_after)
	{
	//	printf("coucou 3\n");
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0 && compare_after_wildcard(buffer, shell) && compare_middle_wildcard(buffer, shell))
	
			return (true);
	}
	else if (shell->wild_before && shell->wild_middle[0])
	{
	//	printf("coucou befmid\n");
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0 && compare_middle_wildcard(buffer, shell))
			return (true);
	}
	else if (shell->wild_before && shell->wild_after)
	{
	//	printf("coucou befaft\n");
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0 && compare_after_wildcard(buffer, shell) == true)
			return (true);
	}
	else if (shell->wild_middle[0] && shell->wild_after)
	{
	//	printf("coucou midaft\n");
		if (compare_middle_wildcard(buffer, shell) && compare_after_wildcard(buffer, shell))
			return (true);
	}
	else if (shell->wild_middle[0])
	{
	//	printf("coucou mid\n");
		if (compare_middle_wildcard(buffer, shell) == true)
			return (true);
	}
	else if (shell->wild_before)
	{
	//	printf("coucou before\n");
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0)
			return (true);
	}
	else if (shell->wild_after)
	{
	//	printf("coucou after\n");
		if (compare_after_wildcard(buffer, shell) == true)
			return (true);
	}
	return (false);
}

char	*remove_newline_from_buffer(char *buffer)
{
	char	*buffer_without_newline;

	//printf("coucou du remove\n");
	if (buffer && strchr(buffer, '\n'))
	{
		buffer_without_newline = ft_strndup(buffer, 0, ft_strlen(buffer) - 1);
		free(buffer);
		//printf("buffwithoutnl=%s\n", buffer_without_newline);
		return (buffer_without_newline);
	}
	//printf("buff=%s\n", buffer);
	return (buffer);
}

char	**get_wildcard_files(t_shell *shell)
{
	char	*buffer;
	int		fd_temp;
	t_tok	*temp;
	
	fd_temp = open(".tmp", O_RDWR, 0644);
	if (fd_temp < 0)
		return (NULL);
	buffer = ft_calloc(1, 1);
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
			temp = shell->user_command->start;
			while (temp)
			{
				printf("list elements: %s\n", temp->var);
				temp = temp->next;
			}
			//printf("YOUPI\n");
		}
	}
	//printf("coucou du get\n");
	remove_wildcard_tok(shell->user_command);
	close(fd_temp);	
	//free les variables et unlink tmp
	return (EXIT_SUCCESS);
}
