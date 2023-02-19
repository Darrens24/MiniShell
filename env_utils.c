/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:44:37 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/19 16:51:48 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// a mettre en donnee de shell pour l'incrementer a chaque appel de ./minishell

int	fill_basic_env(t_shell *shell)
{
	char	*pwd;
	int		sh_level;
	char	*underscore;
	char	*str_sh_level;
	char	*temp;

	sh_level = 1;
	temp = ft_itoa(sh_level);
	pwd = ft_strjoin("PWD=", getcwd(0, 0));
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

	elem = env->end;
	len = ft_strlen(line);
	while (elem)
	{
		if (ft_strncmp(line, elem->variable, len) == 0)
			return (1);
		elem = elem->next;
	}
	return (0);
}
