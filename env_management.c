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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		printf("%s\n", temp->variable);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	option_n(char **command, int i)
{
	int	returnval;
	size_t	x;

	returnval = 0;
	x = 1;
	i++;
	if (command[i] && command[i][0] && command[i][0] == '-')
	{
		while (command[i][x] && command[i][x] == 'n')
			x++;
		if (x == ft_strlen(command[i]) && x != 1)
			returnval = 1;
	}
	return (returnval);
}

int	option_njump(char **command, int i)
{
	size_t	x;

	i++;
	while (command[i] && command[i][0] && command[i][0] == '-')
	{
		x = 1;
		while (command[i][x] && command[i][x] == 'n')
			x++;
		if (x == 1 || x != ft_strlen(command[i]))
			break;
		i++;
	}
	return (i);
}

int	print_echo(char **command)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = option_n(command, i);
	if (tmp && !command[option_njump(command, i)])
		return (EXIT_SUCCESS);
	else if (!command[i + 1])
		return (ft_putchar_fd('\n', STDOUT_FILENO), 1);
	if (tmp)
		i = option_njump(command, i);
	else
		i++;
	while (command[i])
	{
		ft_putstr_fd(command[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (tmp)
		ft_putstr_fd("", STDOUT_FILENO);
	else
		ft_putendl_fd("", STDOUT_FILENO);
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
	else if (temp)
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

int	execute_builtin_cmd(t_shell *shell, int i)
{
	execute_directory_cmd(shell, i);
	if (ft_strncmp(shell->multi_cmd[i][0], "env", 4) == 0)
	{
		if (argument_after_cmd(shell) == TRUE)
			return (printf("Env command won't take arguments or options\n"));
		return (print_list(shell->env_l), EXIT_SUCCESS);
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "export", 7) == 0)
	{
		if (argument_after_cmd(shell) == FALSE)
			return (print_export(shell));
		else
			return (export_variable(shell));
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "unset", 6) == 0)
	{
		if (argument_after_cmd(shell) == FALSE)
			return (EXIT_SUCCESS);
		else
			return (unset_variable(shell));
	}
	else if (ft_strncmp(shell->multi_cmd[i][0], "echo", 5) == 0)
		print_echo(shell->multi_cmd[i]);
	return (EXIT_SUCCESS);
}
