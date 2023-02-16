/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:11:53 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/16 13:38:59 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_is_wildcard(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '*')
			return (true);
	return (false);
}

int	no_wildcard_before(char *str, int index)
{
	while (str && str[index])
	{
		if (str[index] == '*')
			return (false);
		index--;
	}
	return (true);
}

int	cmd_has_wildcard(t_shell *shell)
{
	t_tok	*temp;

	temp = shell->user_command->start;
	while (temp)
	{
		if (string_is_wildcard(temp->var))
			return (true);
		temp = temp->next;
	}
	return (false);
}

int	jump_next_wildcard(char *str, int index)
{
	while (str[index] && str[index] != '*')
		index++;
	//index--;
	return (index);
}

int	jump_previous_wildcard(char *str, int index)
{
	while (str[index] && str[index] != '*')
		index--;
	index++;
	return (index);
}

char	*get_wild_middle(char *str, int index)
{
	char	*middle;
	int		start;

	start = index;
	while (str[index] && str[index] != '*')
		index++;
	middle = ft_strndup(str, start, index);
	return (middle);
}

int	parse_wildcard(t_shell *shell, char **envp)
{
	int		i;
	int		j;
	t_tok	*temp;
	int 	nb_of_wildcard;

	temp = shell->user_command->start;
	while (temp && !string_is_wildcard(temp->var))
		temp = temp->next;
	//printf("var = %s\n", temp->var);
	nb_of_wildcard = get_nb_of_wildcard(temp->var);
	//printf("nb wild = %d\n", nb_of_wildcard);
	if (nb_of_wildcard < 0)
		return (EXIT_FAILURE);
	shell->wild_middle = malloc(sizeof(char *) * (nb_of_wildcard - 1));//normalement -2 mais +1 pour le NULL ----> A FREE a la fin de la substitution de la node wildcard
	if (!shell->wild_middle)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	while (temp->var[i])
	{
		if (temp->var[i] == '*' && i != 0 && no_wildcard_before(temp->var, i - 1) == true)
		{
			shell->wild_before = ft_strndup(temp->var, 0, i);  
		}
		if (temp->var[i] == '*' && temp->var[i + 1] && string_is_wildcard(temp->var + i + 1))
		{
			shell->wild_middle[j] = get_wild_middle(temp->var, i + 1);
			j++;
		}
		if (temp->var[i] == '*' && temp->var[i + 1] && !string_is_wildcard(temp->var + i + 1))
		{
			shell->wild_after = ft_strndup(temp->var, i + 1, ft_strlen(temp->var));
		}
		i++;
	}
	shell->wild_middle[j] = NULL; //peut-etre rajouter une protection
	printf("shell->wild_before : %s\n", shell->wild_before);
	printf("shell->wild_after : %s\n", shell->wild_after);
	printf("shell->wild_middle[0] : %s\n", shell->wild_middle[0]);
	printf("shell->wild_middle[1] : %s\n", shell->wild_middle[1]);
	execute_ls_in_tmp(shell, envp);
	return (EXIT_SUCCESS);
}
