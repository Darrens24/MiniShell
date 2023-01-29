#include "minishell.h"

int	allocate_shell(t_shell *shell, char **envp)
{
	int	i;

	shell->line_readed = ft_calloc(1, 1);
	shell->env_l = malloc(sizeof(*(shell->env_l)));
	if (!shell->env_l)
		return (printf("Malloc: Env failed\n"));
	shell->user_command = malloc(sizeof(*(shell->user_command)));
	if (!shell->user_command)
		return (printf("Malloc: UserCommand failed\n"));
	shell->env_l->nb_elem = 0;
	i = -1;
	while (envp[++i])
		new_back_node(shell->env_l, envp[i]);
	shell->sorted_env_l = malloc(sizeof(*(shell->env_l)));
	if (!shell->sorted_env_l)
		return (printf("Malloc: Sorted Env failed\n"));
	shell->sorted_env_l = sort_list(shell->env_l);
	return (EXIT_SUCCESS);
}

int	clean_memory(t_shell *shell)
{
	free(shell->line_readed);
	free(shell->env_l);
	free(shell->sorted_env_l);
	free(shell->user_command);
	return (EXIT_SUCCESS);
}
