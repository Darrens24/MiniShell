#include "minishell.h"

int	execute_env_cmd(t_shell *shell)
{
	if (!ft_strncmp(shell.line_readed, "env", 4))
	{
		if (argument_after_cmd)
			return (printf("Env command won't take arguments or options\n"));
		print_list(shell->env_l);
	}
	return (EXIT_SUCCESS)
}
