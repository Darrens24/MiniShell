#include "minishell.h"

// char	**get_builtin_args() --> Parsing
/*
int	add_env_variable(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < nb_of_args)
		new_back_node(shell->env_l, shell->builtin_args[i]);
}*/
int	ft_strlenequal(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	return (i);
}
int	envchecker(char *line, t_chained *env)
{
	t_node	*elem;
	int	len;

	elem = env->end;
	len = ft_strlen(line);
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
			return (1);
		elem=elem->next;
	}
	return (0);
}

int	argument_after_cmd(t_shell *shell)
{
	if (shell->user_command->nb_elem > 1)
		return (1);
	return (0);
}

int	print_export(t_shell *shell)
{
	t_node	*temp;
	
	temp = shell->sorted_env_l->start;
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		printf("%s\n", temp->variable);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	option_n(t_shell *shell)
{
	if (shell->user_command->start->next
		&& shell->user_command->start->next->var
		&& !ft_strncmp(shell->user_command->start->next->var, "-n", 3))
			return (1);
	return (0);
}

int	print_echo(t_shell *shell)
{

	t_tok	*temp;

	if (option_n(shell) && shell->user_command->nb_elem == 2)
		return (EXIT_SUCCESS);
	else if (shell->user_command->nb_elem == 1)
		return (ft_putchar_fd('\n', STDOUT_FILENO), 1);
	if (option_n(shell))
		temp = shell->user_command->start->next->next;
	else
		temp = shell->user_command->start->next;
	while (temp->next)
	{
		ft_putstr_fd(temp->var, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		temp = temp->next;
	}
	if (temp->var)
	{
		if (option_n(shell))
			ft_putstr_fd(temp->var, STDOUT_FILENO);
		else
			ft_putendl_fd(temp->var, STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);		
}

t_node	*remove_current_node(t_node *node, t_chained *lst)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	if (!node->next)
	{
		remove_back_node(lst);
		return (node);
	}
	free(node->variable);
	lst->nb_elem--;
	node->variable = NULL;
	node->prev = NULL;
	node->next = NULL;
	free(node);
	node = NULL;
	return (node);
}

int	unset_variable(t_shell *shell)
{
	t_node	*temp;

	temp = shell->sorted_env_l->end;
	while (temp && ft_strncmp(temp->variable, shell->user_command->start->next->var, ft_strlenequal(temp->variable)))
		temp = temp->prev;
	if (shell->sorted_env_l->nb_elem == 1)
		remove_back_node(shell->sorted_env_l);
	else		
		remove_current_node(temp, shell->sorted_env_l);
	return (EXIT_SUCCESS);
}

int	export_variable(t_shell *shell)
{
	if (!envchecker(ft_strndup(shell->user_command->start->next->var, 0, ft_strlenequal(shell->user_command->start->next->var)) , shell->sorted_env_l))
		new_back_node(shell->sorted_env_l, shell->user_command->start->next->var);
	else
	{
		unset_variable(shell);
		new_back_node(shell->sorted_env_l, shell->user_command->start->next->var);
	}
	return (EXIT_SUCCESS);
}

int	execute_builtin_cmd(t_shell *shell)
{
	execute_directory_cmd(shell);
	if (ft_strncmp(shell->user_command->start->var, "env", 4) == 0)
	{
		if (argument_after_cmd(shell) == TRUE)
			return (printf("Env command won't take arguments or options\n"));
		return (print_list(shell->env_l), EXIT_SUCCESS);
	}
	else if (ft_strncmp(shell->user_command->start->var, "export", 7) == 0)
	{
		if (argument_after_cmd(shell) == FALSE)
			return (print_export(shell));
		else
			return (export_variable(shell));
	}
	else if (ft_strncmp(shell->user_command->start->var, "unset", 6) == 0)
	{
		if (argument_after_cmd(shell) == FALSE)
			return (EXIT_SUCCESS);
		else
			return (unset_variable(shell));
	}
	else if (ft_strncmp(shell->user_command->start->var, "echo", 5) == 0)
		print_echo(shell);
	return (EXIT_SUCCESS);
}
