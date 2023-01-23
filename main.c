#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_shell	*shell;

	char*	line;
	const char*	prompt;

	shell = malloc(sizeof(t_shell));
	if (!shell)	
		printf("Malloc: Shell malloc failed\n");
	allocate_shell(shell);
	line = readline(prompt);
	printf("%s\n", line);
	return (0);
}
