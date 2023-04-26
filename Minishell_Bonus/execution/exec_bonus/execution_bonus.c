/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:55:45 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/26 18:54:16 by pfaria-d         ###   ########.fr       */
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
		//printf("coucou qui devrait s'afficher en early out\n");
		early_out_redirection(shell->fd[shell->index_of_pipes]);
	}
	if (shell->index_of_pipes != 0 && shell->last_index != -1
		&& shell->nb_of_pipes == shell->index_of_pipes)
	{		
		//printf("coucou qui devrait s'afficher en inside out\n");
		inside_redirection(shell->fd[shell->index_of_pipes - 1]);
	}
	//if (shell->out == TRUE
	//	&& shell->index_of_pipes == shell->nb_of_pipes)
	//	dup2(shell->outfile, STDOUT_FILENO);
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

	shell->array_env = get_array_env(shell);
	shell->home = ft_strdup(get_home(shell->array_env));
	stat(command[0], &buff);
	if (!is_builtin_command_bonus(command))
	{
		if (access(command[0], F_OK) == 0 && S_ISREG(buff.st_mode))
			tmp = ft_strdup(command[0]);
		else
			tmp = find_path_bonus(command[0], shell);
		if (!tmp)
		{
			if (index > 0)
				close_fds(shell->fd[shell->index_of_pipes - 1]);
			return (EXIT_FAILURE);
		}
		if (shell->index_of_pipes != shell->nb_of_pipes)
			pipe(shell->fd[shell->index_of_pipes]);
		shell->pid[shell->index_of_commands] = fork();
		signal(SIGINT, &do_nothing);
		signal(SIGQUIT, &do_nothing);
		if (shell->pid[shell->index_of_commands] == 0)
		{
			redirection_bonus(shell);
			execve(tmp, command, shell->array_env);
		}
		shell->last_index = shell->index_of_pipes;
		free(tmp);
	}
	//else
	//{
	//	redirection_bonus(shell);
	//	execute_builtin_bonus(command);
	//}
	wait_pids_bonus(shell->pid, shell);
	return (EXIT_SUCCESS);
}

int	is_or(char *cmd)
{
	if (ft_strncmp(cmd, "||", 3) == 0)
		return (1);
	return (0);
}

int	is_and(char *cmd)
{
	if (ft_strncmp(cmd, "&&", 3) == 0)
		return (1);
	return (0);
}

int	is_pipe(char *cmd)
{
	if (ft_strncmp(cmd, "|", 2) == 0)
		return (1);
	return (0);
}

int	execution_bonus(t_shell *shell, t_branch *map)
{
	t_branch	*tmp;

	if (map && map->left)
	{
		printf("left -> %s \n", map->left->cmd[0]);
		if (map && is_and_or(map->cmd[0]))
			return (execution_bonus(shell, map->left));
		else if (map && is_operator(map->cmd[0]) && ++shell->nb_of_pipes)
			return (execution_bonus(shell, map->left));
	}
	else if (map && map->right)
	{
		printf("right -> %s \n", map->right->cmd[0]);
		if (map && is_and_or(map->cmd[0]))
		{
			if (is_and(map->cmd[0]) && map->err_code == 0)
			{
				printf("cc\n");
				return (execution_bonus(shell, map->right));
			}
			else if (is_or(map->cmd[0]) && map->err_code > 0)
				return (execution_bonus(shell, map->right));
			else if (map && is_pipe(map->cmd[0]))
				return (execution_bonus(shell, map->right));
			else
			{
				printf("dad\n");
				tmp = map;
				map = map->dad;
				if (map)
				{
					printf("i clean son\n");
					clean_node(tmp);
					printf("cmd after clean = %s\n", map->cmd[0]);
					return (execution_bonus(shell, map));
				}
				else if (!map)
				{
					printf("OH JE VAIS TOUT CLEAN LA STAFT\n");
					clean_node(shell->tree->start);
					return (EXIT_SUCCESS);
				}
			}
		}
		else if (map && is_operator(map->cmd[0])
			&& shell->nb_of_pipes)
			return (execution_bonus(shell, map->right));
	}
	else if (map && !is_operator(map->cmd[0]))
	{
		printf("execute -> %s | then dad -> %s\n", map->cmd[0], map->dad->cmd[0]);
		tmp = map;
		map = map->dad;
		if (is_pipe(tmp->dad->cmd[0]) && tmp->dad->right == tmp)
			shell->index_of_pipes++;
		//printf("nb_of_pipes = %d | index_of_pipes = %d | last_index = %d\n", shell->nb_of_pipes, shell->index_of_pipes, shell->last_index);
		execute_command_clean_leaf(shell, tmp->cmd);
		clean_node(tmp);
		map->err_code = g_err;
		printf("map error code = %d\n", map->err_code);
		shell->index_of_commands++;
		return (execution_bonus(shell, map));
	}
	else if (map && map->dad)
	{
		if (map && is_pipe(map->cmd[0]))
		{
			if (shell->index_of_pipes > 0 && shell->last_index != -1)
				close_fds(shell->fd[shell->index_of_pipes - 1]);
			if (shell->nb_of_pipes == shell->index_of_pipes)
				shell->last_index = -1;
		}
		printf("dad\n");
		tmp = map;
		map = map->dad;
		map->err_code = tmp->err_code;
		clean_node(tmp);
		return (execution_bonus(shell, map));
	}
	return (EXIT_SUCCESS);
}
