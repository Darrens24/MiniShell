/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:55:45 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/02 19:05:44 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin_command_bonus(char **command)
{
	if (ft_strncmp(command[0], "pwd", 4) == 0
		|| ft_strncmp(command[0], "cd", 3) == 0
		|| ft_strncmp(command[0], "export", 7) == 0
		|| ft_strncmp(command[0], "env", 4) == 0
		|| ft_strncmp(command[0], "unset", 6) == 0
		|| ft_strncmp(command[0], "exit", 5) == 0
		|| ft_strncmp(command[0], "echo", 5) == 0)
		return (TRUE);
	return (FALSE);
}

int	redirection_bonus(t_shell *shell)
{		
	if (shell->index_of_pipes < shell->nb_of_pipes)
	{
		printf("early of pipe = %d\n", shell->index_of_pipes);
		early_out_redirection(shell->fd[shell->index_of_pipes]);
	}
	if (shell->index_of_pipes != 0 && shell->last_index != -1
		&& shell->nb_of_pipes == shell->index_of_pipes)
	{
		printf("inside redirection\n");
		inside_redirection(shell->fd[shell->index_of_pipes - 1]);
	}
	if (shell->out == TRUE
		&& shell->index_of_pipes == shell->nb_of_pipes)
		dup2(shell->outfile, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

char	*get_correct_path_bonus(t_shell *shell, char *command)
{
	int			i;
	struct stat	buff;

	stat(command, &buff);
	shell->correct_path = NULL;
	i = -1;
	while (shell->all_path[++i] && (ft_strlen(command) > 0
			&& !S_ISDIR(buff.st_mode)))
	{
		shell->correct_path = ft_strjoin(shell->all_path[i],
				command);
		if (access(shell->correct_path, F_OK) == 0)
			return (shell->correct_path);
		free(shell->correct_path);
	}
	g_err = 127;
	if (ft_strncmp(".", command, 1) == 0)
		printf("%s: No such file or directory\n", command);
	else
		printf("%s: Command not found\n", command);
	return (NULL);
}

char	*find_path_bonus(char *command, t_shell *shell)
{
	char	*temp;
	char	*all_path;

	all_path = get_path(shell->array_env);
	if (!all_path)
	{
		return (printf("%s : Command not found\n",
				command), NULL);
	}
	shell->all_path = ft_split_slash(all_path, ':');
	if (!shell->all_path[0])
		return (NULL);
	temp = get_correct_path_bonus(shell, command);
	free_array(shell->all_path);
	if (!temp)
		return (NULL);
	return (temp);
}

int	execute_command_clean_leaf(t_shell *shell, char **command)
{
	char		*tmp;
	struct stat	buff;

	tmp = NULL;
	stat(command[0], &buff);
	if (!is_builtin_command_bonus(command))
	{
		not_execute_builtin(shell, command, tmp, buff);
	}
	/*else
	{
		redirection_bonus(shell);
		execute_builtin_bonus(command);
	}*/
	return (EXIT_SUCCESS);
}
