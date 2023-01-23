#include "minishell.h"

int			allocate_shell(t_shell *shell)
{
	shell->history = malloc(sizeof(*shell->history));
	if (!shell->history)
		return (printf("Malloc: History malloc failed\n"));
	shell->history->nb_elem = 0;

	return (0);
}
