#include "minishell.h"

int	allocate_shell(t_shell *shell, char **envp)
{
	int	i;

	shell->line_readed = ft_calloc(1, 1);
	shell->all_path = ft_split_slash(get_path(envp), ':');
	shell->env_l = malloc(sizeof(*(shell->env_l)));
	if (!shell->env_l)
		return (printf("Malloc: Env failed\n"));
	shell->array_env = get_array_env(shell);
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

char	**get_array_env(t_shell *shell)
{
	t_tok	*temp;
	char	**array;
	int		i;

	temp = shell->user_command->start;
	array = malloc(sizeof(char *) * (shell->user_command->nb_elem + 1));
	if (!array)
		return (NULL);
	i = -1;
	while (temp)
	{
		array[++i] = ft_strdup(temp->var);
		temp = temp->next;
	}
	array[i] = NULL;
	return (array);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (EXIT_SUCCESS);
}

int	clean_between_cmds(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < get_number_of_commands(shell))
		free_array(shell->multi_cmd[i]);
	free(shell->multi_cmd);
	clear_toklst(shell->user_command);
	return (EXIT_SUCCESS);
}

int	clean_memory(t_shell *shell)
{
	////int	i;

	//i = -1;
	//while (++i < get_number_of_commands(shell))
	//	free_array(shell->multi_cmd[i]);
	//free(shell->multi_cmd);
	free(shell->line_readed);
	clear_chained_lst(shell->env_l);
	clear_chained_lst(shell->sorted_env_l);
	//free(shell->env_l);
	//free(shell->sorted_env_l);
	//free(shell->correct_path); A FREE UNIQUEMENT SI COMMANDE
	free_array(shell->all_path);
	return (EXIT_SUCCESS);
}

