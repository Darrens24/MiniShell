#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_shell	shell;
	char	*temp;
	const char	*prompt;

	allocate_shell(&shell);
	temp = readline(prompt);
	printf("temp = %s\n", temp);
	new_front_node(shell.history, temp);
	printf("%s\n", shell.history->start->usr_cmd);
	return (0);
}
