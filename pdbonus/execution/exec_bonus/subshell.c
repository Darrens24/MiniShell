#include "../../minishell.h"

int	initialize_subvariables(t_shell *shell)
{
//	shell->current_dir_path = NULL;
//	shell->previous_dir_path = NULL;
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

int	allocate_subshell(t_shell *shell, t_chained *env, t_toklst *user_command, t_chained *export)
{
	shell->env_l = env;
	shell->user_command = user_command;
	shell->sorted_env_l = export;
	initialize_subvariables(shell);
	return (EXIT_SUCCESS);
}

int	subshell(t_toklst *user_command, t_chained *env, t_chained *export)
{
	int		good;
	t_shell	shell;

	allocate_subshell(&shell, env, user_command, export);
	good = TRUE;
	if (good == TRUE && and_or_in_cmd(shell.user_command))
	{
		shell.nb_of_fds_to_malloc = 0;
		shell.bcmd = get_bcmd(shell.user_command, &shell);
		fill_trinary_tree(shell.user_command, &shell);
		execution_bonus(&shell, shell.tree->map);
		free_array(shell.tree->start->cmd);
		free(shell.tree->start);
		free(shell.tree);
		clean_between_cmds(&shell);
	}
	else if (good == TRUE)
		pipe_command(&shell);
	clear_toklst(shell.user_command);
	dup2(shell.saved_stdin, STDIN_FILENO);
	dup2(shell.saved_stdout, STDOUT_FILENO);
	clean_memory(&shell);
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
		exit(0);
	}
	if (shell->index_of_pipes != shell->nb_of_pipes)
	{
		shell->last_index = shell->index_of_pipes;
	}
	return (EXIT_SUCCESS);
}
