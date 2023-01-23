#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	shell;

	allocate_shell(&shell, envp);
	while (ft_strncmp(shell.line_readed, "exit\n", 5))
	{
		print_cwd();
		free(shell.line_readed);
		shell.line_readed = readline(shell.prompt);
		add_history(shell.line_readed);
	}
//	int	i = -1;
//	while (shell.env[++i])
//		printf("%s\n", shell.env[i]);  -->env recupere
//	temp = readline(shell.prompt);
//	add_history(temp);
//	new_front_node(shell.history, temp);
//	printf("%s\n", shell.history->start->usr_cmd);
	return (0);
}
