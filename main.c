#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	*shell;

	shell = malloc(sizeof(*shell));
	allocate_shell(shell, envp);
/*	while (shell->line_readed && ft_strncmp(shell->line_readed, "exit", 5))
	{
		free(shell->line_readed);
		print_cwd_linux();
		shell->line_readed = readline(shell->prompt);
		add_history(shell->line_readed);
	}*/
	print_list(shell->env_l);
	return (0);
}
