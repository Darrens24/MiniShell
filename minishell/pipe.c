/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/23 12:04:16 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_to_malloc(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

int	initialize_elem(t_cmd *elem, int exec, int i)
{
	elem->var[i] = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	elem->exec = exec;
	return (EXIT_SUCCESS);
}

t_cmdlst	*newp_back_cmd(t_cmdlst *cmdlst, char **command, int exec)
{
	t_cmd	*elem;
	int		i;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->var = malloc(sizeof(char *) * (size_to_malloc(command) + 1));
	i = -1;
	while (command[++i])
		elem->var[i] = ft_strdup(command[i]);
	initialize_elem(elem, exec, i);
	if (cmdlst->nb_elem == 0)
	{
		cmdlst->start = elem;
		cmdlst->end = elem;
	}
	else
	{
		cmdlst->end->next = elem;
		elem->prev = cmdlst->end;
		cmdlst->end = elem;
	}
	cmdlst->nb_elem++;
	return (cmdlst);
}

int	builtin_manager(t_shell *shell, int index, t_cmd *cmd)
{
	if (get_number_of_commands(shell) == 1)
	{
		redirection_parsing(shell, index, cmd);
		execute_builtin_cmd(shell, index);
	}
	else if (get_number_of_commands(shell) > 1)
	{
		shell->pid[index] = fork();
		if (shell->pid[index] == 0)
		{
			redirection_parsing(shell, index, cmd);
			execute_builtin_cmd(shell, index);
			exit(1);
		}
	}
	return (EXIT_SUCCESS);
}

int	slash_manager(t_cmd *cmd)
{
	int			access_return;
	struct stat	buff;

	access_return = 0;
	if (cmd->var[0][0] == '/')
	{
		access_return = access(cmd->var[0], X_OK);
		if (access_return < 0)
		{
			g_err = 126;
			printf("%s : Permission denied\n", cmd->var[0]);
			return (EXIT_FAILURE);
		}
		stat(cmd->var[0], &buff);
		if (S_ISDIR(buff.st_mode))
		{
			g_err = 126;
			printf("%s : Is a directory\n", cmd->var[0]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	execute_commands(t_cmd *cmd, int index, t_shell *shell, int i)
{
	char	*temp;

	if (!is_builtin_command(cmd))
	{
		if (slash_manager(cmd) != 0)
			return (EXIT_FAILURE);
		if (access(cmd->var[0], F_OK) == 0)
			temp = ft_strdup(cmd->var[0]);
		else
			temp = find_path(cmd, shell);
		if (!temp)
		{
			if (index > 0 && cmd->exec == 0)
				close_fds(shell->fd[index - 1]);
			return (EXIT_FAILURE);
		}
		shell->pid[i] = fork();
		signal(SIGINT, &do_nothing);
		signal(SIGQUIT, &do_nothing);
		if (shell->pid[i] == 0)
		{
			if (cmd->exec == 0 || (cmd->next && cmd->next->exec == 0))
				redirection_parsing(shell, index, cmd);
			execve(temp, cmd->var, shell->array_env);
		}
		free(temp);
	}
	else
		builtin_manager(shell, index, cmd);
	if (index > 0 && cmd->exec == 0)
		close_fds(shell->fd[index - 1]);
	return (EXIT_SUCCESS);
}

int	redirect_and_execute_cmd(t_cmd *cmd, int index, t_shell *shell, int i)
{
	execute_commands(cmd, index, shell, i);
	return (EXIT_SUCCESS);
}

int	final_redirection(t_shell *shell)
{
	if (shell->out == TRUE)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		shell->out = FALSE;
	}
	dup2(shell->saved_stdin, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

t_cmdlst	*createcmdlst(t_shell *shell, int i)
{
	t_tok		*t;
	t_cmdlst	*cmdlst;

	t = shell->user_command->start;
	cmdlst = malloc(sizeof(t_cmdlst));
	while (shell->multi_cmd[++i])
	{
		if (i != 0 && shell->multi_cmd[i])
		{
			while (t && !((ft_strncmp(t->var, "|", 2) != 0 && t->quote == 0)
					|| (ft_strncmp(t->var, "||", 3) != 0 && t->quote == 0)
					|| (ft_strncmp(t->var, "&&", 3) != 0 && t->quote == 0)))
				t = t->next;
			if (t && ft_strncmp(t->var, "||", 3) == 0 && t->quote == 0)
				cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 1);
			else if (t && ft_strncmp(t->var, "&&", 3) == 0 && t->quote == 0)
				cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 2);
			else
				cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 0);
			t = t->next;
		}
		else
			cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 0);
	}
	return (cmdlst);
}

int	pipe_command(t_shell *shell)
{
	int			i;
	t_cmdlst	*cmdlst;
	t_cmd		*cmd;
	int			index;

	i = -1;
	get_array_cmd_and_pipe_fds(shell);
	shell->array_env = get_array_env(shell);
	shell->home = ft_strdup(get_home(shell->array_env));
	cmdlst = createcmdlst(shell, i);
	cmd = cmdlst->start;
	i = 0;
	index = 0;
	while (shell->user_command->nb_elem != 0 && cmd)
	{
		if (cmd->next && cmd->next->exec == 0)
		{
			if (pipe(shell->fd[i]) < 0)
				return (printf("Pipe failed\n"));
			if (cmd->exec != 0)
				i = 0;
		}
		redirect_and_execute_cmd(cmd, i, shell, index);
		cmd = cmd->next;
		index++;
		if (cmd && cmd->exec == 0)
			i++;
	}
	wait_pids(shell->pid, shell);
	final_redirection(shell);
	//clean_between_cmds(shell);
	return (EXIT_SUCCESS);
}
