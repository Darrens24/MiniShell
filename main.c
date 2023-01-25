#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	shell;

	//shell = malloc(sizeof(t_shell));
	allocate_shell(&shell, envp);
	while (shell.line_readed && ft_strncmp(shell.line_readed, "exit", 5))
	{
		free(shell.line_readed);
		//print_cwd_linux();
		cyan();
		shell.line_readed = readline(getcwd(NULL, 0), reset());
		reset();
		if (ft_strncmp(shell.line_readed, "pwd", 4) == 0)
			print_pwd_linux();
		add_history(shell.line_readed);
	}
	return (0);
}
