/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:53:45 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/14 17:32:35 by eleleux          ###   ########.fr       */
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
	find_occurence_in_tmp(shell, fd_temp);
	//unlink(".tmp"); --> a la toute fin de la traduction des wildcards
	return (EXIT_SUCCESS);
}

int	get_wildcard_index(t_shell *shell, char *buffer)
{
}

int	find_occurence_in_tmp(t_shell *shell)
{
	char	*buffer = ft_calloc(1, 1);
	int		nb_of_files = 0;
	//char	**stock;
	//int		next_wild_index = 0;
	
	fd_temp = open(".tmp", O_RDWR, 0644);
	if (fd_temp < 0)
		return (printf("Temp opening failed\n"));
	while (buffer)
	{	
		free(buffer);
		buffer = get_next_line(fd_temp);
		printf("buffer = %s\n", buffer);
		if (!buffer)
			break ;
		next_wild_index = get_wildcard_index(shell, buffer);
		if (ft_strncmp(buffer, shell->wild_before, ft_strlen(shell->wild_before)) == 0)
			nb_of_files++;
		/*if (ft_strncmp(buffer + next_wild_index + 1, shell->wild_after, ft_strlen(shell->wild_after)) == 0)
			nb_of_files++;*/
	}//ceci est une recuperation du nombre d'elements a malloc dans stock
	//maintenant, il faut reprendre la boucle et recuperer ces elements
	printf("nb file : %d\n", nb_of_files);
	return (EXIT_SUCCESS);
}
