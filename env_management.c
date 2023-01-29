#include "minishell.h"

/*static int	argument_after_cmd(void)
{
	return (0);
}*/

// char	**get_builtin_args() --> Parsing
/*
int	add_env_variable(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < nb_of_args)
		new_back_node(shell->env_l, shell->builtin_args[i]);
}*/

int	print_export(t_shell *shell)
{
	t_node	*temp;
	
	temp = shell->sorted_env_l->start;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		printf("%s\n", temp->variable);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
/*
int	print_echo(t_shell *shell)
{
	int	i;

	if (option_n && !argument_after_cmd)
		return (EXIT_SUCCESS);
	else if (!argument_after_cmd)
		return (ft_putchar_fd('\n', STDOUT_FILENO), EXIT_SUCCESS);
	i = 0;
	while (i < number_of_args - 1)
		ft_putstr_fd(shell->builtin_args[i++], STDOUT_FILENO);
	if (option_n)
		ft_putstr_fd(shell->builtin_args[i], STDOUT_FILENO);
	else
		ft_putendl_fd(shell->builtin_args[i], STDOUT_FILENO);
	return (EXIT_SUCCESS);		
}*/

int	export_variable(t_shell *shell)
{
	new_back_node(shell->sorted_env_l, shell->user_command->start->next->variable);
	return (EXIT_SUCCESS);
}

int	argument_after_cmd(t_shell *shell)
{
	if (shell->user_command->nb_elem > 1)
		return (1);
	return (0);
}

int	execute_env_cmd(t_shell *shell)
{
	if (ft_strncmp(shell->user_command->start->variable, "env", 4) == 0)
	{
		if (argument_after_cmd(shell) == TRUE)
			return (printf("Env command won't take arguments or options\n"));
		return (print_list(shell->env_l), EXIT_SUCCESS);
	}
	else if (ft_strncmp(shell->user_command->start->variable, "export", 7) == 0)
	{
		if (argument_after_cmd(shell) == FALSE)
			return (print_export(shell));
		else
			return (export_variable(shell));
	}
//	else if (ft_strncmp(shell->line_readed, "echo", 5) == 0)
//		print_echo(shell);
	return (EXIT_SUCCESS);
}
