#include "minishell.h"

int			allocate_shell(t_shell *shell, char **envp)
{
	int	i;

	shell->history = malloc(sizeof(*shell->history));
	if (!shell->history)
		return (printf("Malloc: History failed\n"));
	shell->line_readed = ft_calloc(1, 1);
	shell->history->nb_elem = 0;
	i = 0;
	while (envp[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		return (printf("Malloc: Env failed\n"));
	i = -1;
	while (envp[++i])
		shell->env[i] = ft_strdup(envp[i]);
	shell->env[i] = NULL;

	return (0);
}
