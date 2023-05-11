/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:24:18 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/11 16:18:49 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	printnoaccess(char **command)
{
	g_err = 127;
	printf("%s : No such file or directory\n",
		command[0]);
	return (127);
}

int	initialize_subvariables(t_shell *shell)
{
	shell->all_path = NULL;
	shell->array_env = NULL;
	shell->multi_cmd = NULL;
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
	shell->nb_of_pipes = 0;
	shell->index_of_pipes = 0;
	shell->last_index = -1;
	shell->index_of_commands = 0;
	shell->index_of_pid = 0;
	shell->valid_pipe = 0;
	return (EXIT_SUCCESS);
}

int	allocate_subshell(t_shell *shell, t_chained *env,
	t_toklst *user_command, t_chained *export)
{
	shell->env_l = env;
	shell->user_command = user_command;
	shell->sorted_env_l = export;
	initialize_subvariables(shell);
	return (EXIT_SUCCESS);
}

int	subshell(t_toklst *user_command, t_chained *env, t_chained *export)
{
	t_shell	subshell;

	allocate_subshell(&subshell, env, user_command, export);
	subshell.nb_of_fds_to_malloc = 0;
	subshell.bcmd = get_bcmd(subshell.user_command, &subshell);
	fill_trinary_tree(subshell.user_command, &subshell);
	execution_bonus(&subshell, subshell.tree->map);
	free_array(subshell.tree->start->cmd);
	free(subshell.tree->start);
	free(subshell.tree);
	clear_toklst(subshell.user_command);
	dup2(subshell.saved_stdin, STDIN_FILENO);
	dup2(subshell.saved_stdout, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	execute_subshell(t_shell *shell, t_branch *map)
{
	if (shell->index_of_pipes != shell->nb_of_pipes)
		pipe(shell->fd[shell->index_of_pipes]);
	shell->pid[shell->index_of_commands] = fork();
	signal(SIGINT, &do_nothing);
	signal(SIGQUIT, &do_nothing);
	if (shell->pid[shell->index_of_commands] == 0)
	{
		redirection_bonus(shell);
		subshell(map->subshell, shell->env_l, shell->sorted_env_l);
		exit(g_err);
	}
	if (shell->index_of_pipes != shell->nb_of_pipes)
		shell->last_index = shell->index_of_pipes;
	return (EXIT_SUCCESS);
}
