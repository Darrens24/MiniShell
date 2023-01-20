#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));

	shell->line_from_prompt = readline(shell->prompt);
	printf("%s\n", shell->line_from_prompt);
	free(shell->line_from_prompt);
	return (0);
}
