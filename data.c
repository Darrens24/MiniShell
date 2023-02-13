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
	i = -1;
	while (envp[++i])
		new_back_node(shell->env_l, envp[i]);
	shell->home = ft_strdup(get_home(envp));
	shell->sorted_env_l = malloc(sizeof(*(shell->env_l)));
	if (!shell->sorted_env_l)
		return (printf("Malloc: Sorted Env failed\n"));
	shell->sorted_env_l = sort_list(shell->env_l);
	initialize_variables(shell);
	return (EXIT_SUCCESS);
}

int	initialize_variables(t_shell *shell)
{
	shell->array_env = NULL;
	shell->user_command->nb_elem = 0;
	shell->env_l->nb_elem = 0;
	shell->multi_cmd = NULL;
	shell->out = FALSE;
	shell->current_dir_path = getcwd(NULL, 0);
	shell->previous_dir_path = getcwd(NULL, 0);
	return (EXIT_SUCCESS);
}

char	**get_array_env(t_shell *shell)
{
	t_node	*temp;
	char	**array;
	int		i;

	temp = shell->sorted_env_l->start;
	array = malloc(sizeof(char *) * (shell->sorted_env_l->nb_elem + 1));
	if (!array)
		return (NULL);
	i = -1;
	while (temp)
	{
		array[++i] = ft_strdup(temp->variable);
		//printf("%d -> %s\n", i, array[i]);
		temp = temp->next;
	}
	array[i] = NULL;
	return (array);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (EXIT_SUCCESS);
}

int	clean_between_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	if (!is_builtin_command(shell, i))
		free_array(shell->array_env);
	if (shell->multi_cmd)
	{
		while (i < get_number_of_commands(shell))
		{
			free_array(shell->multi_cmd[i]);
			i++;
		}
		free(shell->multi_cmd);
		shell->multi_cmd = NULL;
	}
	clear_toklst(shell->user_command);
	//free(shell->correct_path);
	free_pids_fds(shell);
		//free_array(shell->all_path);
	return (EXIT_SUCCESS);
}

int	clean_memory(t_shell *shell)
{
	free(shell->home);
	free(shell->line_readed);
	clear_chained_lst(shell->env_l);
	clear_chained_lst(shell->sorted_env_l);
	free(shell->env_l);
	free(shell->sorted_env_l);
	free(shell->user_command);
	return (EXIT_SUCCESS);
}

