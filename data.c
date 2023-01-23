#include "minishell.h"

int			allocate_shell(t_shell *shell)
{
	shell->history = malloc(sizeof(t_chained));
	if (!shell->history)
		return (printf("Malloc: History malloc failed\n"));

	return (0);
}
