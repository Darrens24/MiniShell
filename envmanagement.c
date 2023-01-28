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

	temp = shell->env_l->start;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(temp->variable, 1);
		temp = temp->next;
	}
	return (1);
}

int	execute_env_cmd(t_shell *shell)
{


	if (ft_strncmp(shell->line_readed, "env", 4) == 0)
	{
//		if (argument_after_cmd)
//			return (printf("Env command won't take arguments or options\n"));
		return (print_list(shell->env_l), 1);
	}
	else if (ft_strncmp(shell->line_readed, "export", 7) == 0)
	{
//		if (!argument_after_cmd)
			return (print_export(shell));
	}
	return (EXIT_SUCCESS);
}
