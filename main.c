#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	shell;
//	char	*temp;

	allocate_shell(&shell, envp);
	int	i = -1;
	while (shell.env[++i])
		printf("%s\n", shell.env[i]);
//	temp = readline(shell.prompt);
//	add_history(temp);
//	new_front_node(shell.history, temp);
//	printf("%s\n", shell.history->start->usr_cmd);
	return (0);
}
