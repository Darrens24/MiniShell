#include "minishell.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	return (envp[i] + 5);
}

char	*get_correct_path(t_shell *shell)
{
	int	i;

	i = 0;
	shell->correct_path = NULL;
	while (shell->all_path[i])
	{
		shell->correct_path = ft_strjoin(shell->all_path[i++], shell->user_command->start->var);
		if (access(shell->correct_path, F_OK) == 0)
			return (shell->correct_path);
		free(shell->correct_path);
	}
	printf("Command not found\n");
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
	return (EXIT_SUCCESS);
}

char	**get_array_command(t_shell *shell)
{
	t_tok	*temp;
	int	i;
	
	shell->array_command = malloc(sizeof(char *) * (shell->user_command->nb_elem + 1));
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

int	command_manager(t_shell *shell, char **envp)
{
//	get_correct_path(shell);
	/*int	i = 0;
	char **res = get_array_command(shell);
	while (res[i])
	{
		printf("arraycommand %d is %s\n",i, res[i]);
		i++;
	}*/
	if (pipe_case)
		execupe_pipe_command(shell, envp);
	else if (get_correct_path(shell))
		execute_command(shell, envp);
	return (EXIT_SUCCESS);
}
