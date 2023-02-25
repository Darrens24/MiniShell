/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:44:37 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/25 10:53:48 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_shell(t_shell *shell)
{
	if (get_number_of_commands(shell) > 1)
		return (EXIT_SUCCESS);
	if (shell->multi_cmd[0][1] && ft_strisdigit(shell->multi_cmd[0][1]))
	{
		if (shell->multi_cmd[0][2])
		{
			g_err = 1;
			return (printf("exit: too many arguments\n"));
		}
		g_err = ft_atoi(shell->multi_cmd[0][1]);
	}
	else if (shell->multi_cmd[0][1] && !ft_strisdigit(shell->multi_cmd[0][1]))
	{
		printf("exit: %s: numeric argument required\n", shell->multi_cmd[0][1]);
		g_err = 255;
	}
	clear_toklst(shell->user_command);
	clean_memory(shell);
	printf(YEL "Exit Minishell\n" WHT);
	exit(g_err);
	return (EXIT_SUCCESS);
}

char	**get_array_env(t_shell *shell)
{
	t_node	*temp;
	char	**array;
	int		i;

	temp = shell->sorted_env_l->start;
	array = malloc(sizeof(char *) * (shell->sorted_env_l->nb_elem + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (temp)
	{
		array[i] = ft_strdup(temp->variable);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	fill_basic_env(t_shell *shell)
{
	char	*pwd;
	char	*underscore;
	char	*str_sh_level;
	char	*temp;
	char	*cwd;

	temp = ft_itoa(1);
	cwd = getcwd(0, 0);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	str_sh_level = ft_strjoin("SHLVL=", temp);
	free(temp);
	underscore = ft_strjoin("_=", "/usr/bin/env");
	new_back_node(shell->env_l, pwd);
	new_back_node(shell->env_l, str_sh_level);
	new_back_node(shell->env_l, underscore);
	free(underscore);
	free(pwd);
	free(str_sh_level);
	return (EXIT_SUCCESS);
}

int	envchecker(char *line, t_chained *env)
{
	t_node	*elem;
	int		len;

	elem = env->start;
	len = ft_strlen(line);
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
			return (1);
		elem = elem->next;
	}
	return (0);
}

int	envindex(char *line, t_chained *env)
{
	t_node	*elem;
	int		len;
	int		index;

	elem = env->start;
	len = ft_strlen(line);
	index = 0;
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
			return (index);
		elem = elem->next;
		index++;
	}
	return (-1);
}
