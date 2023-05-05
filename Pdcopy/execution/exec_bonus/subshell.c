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
	/* int		good; */
	t_shell	subshell;

	allocate_subshell(&subshell, env, user_command, export);
	printf("COUCOU\n");
	/* good = TRUE; */
	/* if (good == TRUE && and_or_in_cmd(subshell.user_command)) */
	/* { */
		subshell.nb_of_fds_to_malloc = 0;
		subshell.bcmd = get_bcmd(subshell.user_command, &subshell);
		fill_trinary_tree(subshell.user_command, &subshell);
		execution_bonus(&subshell, subshell.tree->map);
		free_array(subshell.tree->start->cmd);
		free(subshell.tree->start);
		free(subshell.tree);
		/* fprintf(stderr, "on va clean between dans le subshell\n"); */
	//	clean_between_cmds(&subshell);
	/* } */
	/* else if (good == TRUE) */
	/* 	pipe_command(&subshell); */
	clear_toklst(subshell.user_command);
	dup2(subshell.saved_stdin, STDIN_FILENO);
	dup2(subshell.saved_stdout, STDOUT_FILENO);
	//clean_memory(&subshell);
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
	//	fprintf(stderr, "le code d'erreur est = %d\n", g_err);
		exit(g_err);
	}
	if (shell->index_of_pipes != shell->nb_of_pipes)
	{
		shell->last_index = shell->index_of_pipes;
	}
	return (EXIT_SUCCESS);
}
