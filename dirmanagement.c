/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirmanagement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:55 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/01/27 13:12:24 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_directory_cmd(t_shell *shell)
{
	if (ft_strncmp(shell->line_readed, "pwd", 4) == 0)
		return (print_pwd_linux());
	else if (ft_strncmp(shell->line_readed, "cd", 4) == 0)
		return (change_directory(shell->dir_path));
	return (FALSE);
}

int	print_pwd_linux(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	printf("%s\n", directory);
	free(directory);
	directory = NULL;
	return (EXIT_SUCCESS);
}

int	change_directory(const char *path)
{
	if (chdir(path) < 0)
		return (printf("Can't find this path bro\n"));
	return (EXIT_SUCCESS);
}
