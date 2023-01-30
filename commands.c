#include "minishell.h"

int	command_manager(t_shell *shell)
{
	get_path_with_slash(shell, envp);
	get_command_in_tokens(shell);
	execute_command(shell);

	return (EXIT_SUCCESS);
}
