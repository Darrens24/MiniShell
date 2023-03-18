/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:54:10 by eleleux           #+#    #+#             */
/*   Updated: 2023/03/18 14:29:16 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	execute_commands(t_cmd *cmd, int index, t_shell *shell, char *temp, int i)
{
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
	char	*temp;

	temp = NULL;
	if (cmd->exec == 1)
	{
		if (g_err != 0)
			execute_commands(cmd, index, shell, temp, i);
	}
	else if (cmd->exec == 2)
	{
		if (g_err == 0)
			execute_commands(cmd, index, shell, temp, i);
	}
	else
		execute_commands(cmd, index, shell, temp, i);
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
	int			prio;
	t_cmdlst	*cmdlst;
	int			tmp;

	t = shell->user_command->start;
	prio = 0;
	cmdlst = malloc(sizeof(t_cmdlst));
	cmdlst->nb_elem = 0;
	while (shell->multi_cmd[++i])
	{
		if (i != 0 && shell->multi_cmd[i])
		{
			while (t && ft_strncmp(t->var, "(", 2) == 0 && prio++ > -10)
				t = t->next;
			while (t && ft_strncmp(t->var, ")", 2) == 0 && prio-- > -10)
				t = t->next;
			while (t && !((ft_strncmp(t->var, "|", 2) != 0 && t->quote == 0)
					|| (ft_strncmp(t->var, "||", 3) != 0 && t->quote == 0)
					|| (ft_strncmp(t->var, "&&", 3) != 0 && t->quote == 0)))
				t = t->next;
			tmp = prio;
			if (t && t->next)
			{
				while (t && t->next && ft_strncmp(t->next->var, "(", 2) == 0 && tmp++ > -10)
					t = t->next;
				while (t && t->next && ft_strncmp(t->next->var, ")", 2) == 0 && tmp-- > -10)
					t = t->next;
			}
			if (t && ft_strncmp(t->var, "||", 3) == 0 && t->quote == 0)
				cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 1, tmp);
			else if (t && ft_strncmp(t->var, "&&", 3) == 0 && t->quote == 0)
				cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 2, tmp);
			else
				cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 0, tmp);
			while (tmp > prio && tmp--)
				t = t->prev;
			t = t->next;
		}
		else
		{
			while (t && ft_strncmp(t->var, "(", 2) == 0 && prio++ > -10)
				t = t->next;
			while (t && ft_strncmp(t->var, ")", 2) == 0 && prio-- > -10)
				t = t->next;
			cmdlst = newp_back_cmd(cmdlst, shell->multi_cmd[i], 0, prio);
		}
	}
	return (cmdlst);
}

t_oplst	*new_back_op(t_oplst *oplst, t_cmdlst *cmdlst)
{
	t_op	*elem;

	elem = malloc(sizeof(t_op));
	if (!elem)
		return (NULL);
	elem->cmdlst = cmdlst;
	elem->next = NULL;
	elem->prev = NULL;
	if (oplst->nb_elem == 0)
	{
		oplst->start = elem;
		oplst->end = elem;
	}
	else
	{
		oplst->end->next = elem;
		elem->prev = oplst->end;
		oplst->end = elem;
	}
	oplst->nb_elem++;
	return (oplst);
}

t_oplst *new_back_oplst(t_oplst *oplst, t_cmd *cmd)
{
	int			i;
	t_cmdlst	*tmp;

	tmp = malloc(sizeof(t_cmdlst));
	tmp->nb_elem = 0;
	i = cmd->exec;
	while ((cmd && cmd->exec == i) || (cmd && cmd->exec == 0) || (cmd && cmd->prev && cmd->prev->prio == cmd->prio && cmd->prio != 0))
	{
		tmp = newp_back_cmd(tmp, cmd->var, cmd->exec, cmd->prio);
		cmd = cmd->next;
	}
	oplst = new_back_op(oplst, tmp);
	return (oplst);
}

t_oplst *createop(t_shell *shell)
{
	t_cmd		*cmd;
	t_oplst		*oplst;
	int			y;
	int			x = 0;

	oplst = malloc(sizeof(t_oplst));
	oplst->nb_elem = 0;
	cmd = shell->cmdlst->start;
	while (cmd)
	{
		y = cmd->exec;
		oplst = new_back_oplst(oplst, cmd);
		while ((cmd && cmd->exec == y) || (cmd && cmd->exec == 0) || (cmd && cmd->prev && cmd->prev->prio == cmd->prio && cmd->prio != 0))
		{
			cmd = cmd->next;
		}
		x++;
	}
	return (oplst);
}

void	printoplst(t_oplst *oplst)
{
	t_op	*op;
	t_cmd	*tmp;
	int		i;

	op = oplst->start;
	while (op)
	{
		i = -1;
		printf("------------------\n");
		tmp = op->cmdlst->start;
		while (tmp)
		{
			while (tmp->var[++i])
				printf("var[%d] = %s, prio = %d\n", i, tmp->var[i], tmp->prio);
			tmp = tmp->next;
		}
		op = op->next;
	}
	printf("------------------\n");
}

int	pipe_command(t_shell *shell)
{
	int			i;
	t_cmd		*temp;
	int			index;
	t_oplst		*op;
	t_op		*optmp;

	i = -1;
	get_array_cmd_and_pipe_fds(shell);
	shell->array_env = get_array_env(shell);
	shell->home = ft_strdup(get_home(shell->array_env));
	shell->cmdlst = createcmdlst(shell, i);
	op = createop(shell);
	/*
	int	y = -1;
	while (shell->multi_cmd[++y])
	{
		printf("-=================-\n");
		int	x = -1;
		while (shell->multi_cmd[y][++x])
			printf("multi_cmd[%d][%d] = %s\n", y, x, shell->multi_cmd[y][x]);
	}
	printf("-=================-\n");
	*/
	//printoplst(op);
	i = 0;
	index = 0;
	optmp = op->start;
	while (optmp && optmp->cmdlst)
	{
		temp = optmp->cmdlst->start;
		while (shell->user_command->nb_elem != 0 && temp)
		{
			if (temp->next && temp->next->exec == 0)
			{
				if (pipe(shell->fd[i]) < 0)
					return (printf("Pipe failed\n"));
			}
			redirect_and_execute_cmd(temp, i, shell, index);
			temp = temp->next;
			index++;
			if (temp && temp->exec == 0)
				i++;
		}
		wait_pids(shell->pid);
		optmp = optmp->next;
	}
	final_redirection(shell);
	clean_between_cmds(shell);
	return (EXIT_SUCCESS);
}
