#include "minishell.h"

char	*get_path(char **array_env)
{
	int	i;

	i = 0;
	while (array_env[i])
	{
		if (ft_strncmp(array_env[i], "PATH=", 5) == 0)
			return (array_env[i] + 5);
		i++;
	}
	printf("Can't find path if you unset it...\n");
	return (NULL);
}

char	*get_correct_path(t_shell *shell, int index)
{
	int	i;

	/*i = -1;
	while (shell->all_path && shell->all_path[++i])
		printf("arrayenv[%d] = %s\n",i, shell->all_path[i]);*/
	shell->correct_path = NULL;
	i = -1;
	while (shell->all_path[++i])
	{
		shell->correct_path = ft_strjoin(shell->all_path[i], shell->multi_cmd[index][0]);
		if (access(shell->correct_path, F_OK) == 0)
			return (shell->correct_path);
		else if (access(shell->multi_cmd[index][0], F_OK) == 0)// && access(shell->multi_cmd[index][0], X_OK) == ENOTDIR)
			return (shell->multi_cmd[index][0]);
		free(shell->correct_path);
	}
	if (shell->multi_cmd[0][0][0] == '/')
	{
		/*if (access(shell->multi_cmd[index][0], F_OK) != ENOTDIR)
			printf("%s : is a directory\n", shell->multi_cmd[index][0]);
		else*/
			printf("%s : Permission denied\n", shell->multi_cmd[index][0]);
	}
	else
		printf("%s : Command not found\n", shell->multi_cmd[index][0]);
	return (NULL);
}

int	execute_command(t_shell *shell, char **envp)
{
	int	pid;
	char	**command;

	command = get_array_command(shell);
	pid = fork();
	if (pid == 0)
		execve(shell->correct_path, command, envp);
	waitpid(pid, 0, 0);
	free_array(command);
	return (EXIT_SUCCESS);
}

char	**get_array_command(t_shell *shell)
{
	t_tok	*temp;
	int	i;
	
	shell->array_command = malloc(sizeof(char *) * (shell->user_command->nb_elem + 1)); // A FREE
	if (!shell->array_command)
		return (NULL);
	temp = shell->user_command->start;
	i = 0;
	while (temp)
	{
		shell->array_command[i++] = ft_strdup(temp->var);
		temp = temp->next;
	}
	shell->array_command[i] = NULL;
	return (shell->array_command);
}

char	**get_command_in_tok(t_shell *shell, int index)
{
	char	**command;
	t_tok	*temp = NULL;
	int		nb_of_args = 0;
	int		i = 0;

	temp = go_to_next_pipe(shell, temp, index);
	while (temp && temp->quote == 1)
	{
		temp = temp->next;
		nb_of_args++;
	}
	command = malloc(sizeof(char *) * (nb_of_args + 1));
	if (!command)
		return (NULL);
	temp = go_to_next_pipe(shell, temp, index);	
	i = 0;
	while (temp && i < nb_of_args)
	{
		command[i] = ft_strdup(temp->var);
		i++;
		temp = temp->next;
	}
	command[i] = NULL;
	return (command);
}
/*
int	command_manager(t_shell *shell, char **envp)
{
//	get_correct_path(shell);
	int	i = 0;
	char **res = get_array_command(shell);
	while (res[i])
	{
		printf("arraycommand %d is %s\n",i, res[i]);
		i++;
	}
	//if (pipe_case)
	//	execupe_pipe_command(shell, envp);
//	if (get_correct_path(shell))
	execute_command(shell, envp);
	return (EXIT_SUCCESS);
}*/
