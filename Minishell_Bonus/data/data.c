/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:49:27 by eleleux           #+#    #+#             */
/*   Updated: 2023/05/09 09:01:43 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	allocate_shell(t_shell *shell, char **envp)
{
	int	i;

	shell->line_readed = ft_calloc(1, 1);
	shell->env_l = malloc(sizeof(*(shell->env_l)));
	if (!shell->env_l)
		return (printf("Malloc: Env failed\n"));
	shell->user_command = malloc(sizeof(*(shell->user_command)));
	if (!shell->user_command)
		return (printf("Malloc: UserCommand failed\n"));
	shell->env_l->nb_elem = 0;
	i = -1;
	while (envp[++i])
		new_back_node(shell->env_l, envp[i]);
	if (i == 0)
		fill_basic_env(shell);
	increment_sh_level(shell);
	shell->sorted_env_l = sort_list(shell->env_l);
	if (i == 0)
		new_front_node(shell->sorted_env_l, "OLDPWD");
	shell->ls_cmd = malloc(sizeof(char *) * 2);
	if (!shell->ls_cmd)
		return (printf("Malloc: LsCommand failed\n"));
	initialize_variables(shell);
	return (EXIT_SUCCESS);
}

int	initialize_variables(t_shell *shell)
{
	shell->current_dir_path = NULL;
	shell->previous_dir_path = NULL;
	shell->all_path = NULL;
	shell->array_env = NULL;
	shell->user_command->nb_elem = 0;
	shell->multi_cmd = NULL;
	shell->out = FALSE;
	shell->ls_cmd[0] = ft_strdup("ls");
	shell->ls_cmd[1] = NULL;
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
	shell->nb_of_pipes = 0;
	shell->index_of_pipes = 0;
	shell->last_index = -1;
	shell->index_of_commands = 0;
	shell->index_of_pid = 0;
	shell->valid_pipe = 0;
	return (EXIT_SUCCESS);
}

int	increment_sh_level(t_shell *shell)
{
	t_increment	*incr;

	incr = malloc(sizeof(t_increment));
	incr->sh = 0;
	incr->i = 0;
	incr->temp = shell->env_l->start;
	while (incr->temp && ft_strncmp(incr->temp->variable, "SHLVL=", 6))
	{
		incr->temp = incr->temp->next;
		incr->i++;
	}
	if (incr->temp)
	{
		incr->sh_level = ft_strndup(incr->temp->variable, 6,
				ft_strlen(incr->temp->variable));
		incr->sh = ft_atoi(incr->sh_level) + 1;
		incr->itoa_sh = ft_itoa(incr->sh);
		remove_current_node(incr->temp, shell->env_l);
		incr->new_sh_level = ft_strjoin("SHLVL=", incr->itoa_sh);
		new_current_node(shell->env_l, incr->i, incr->new_sh_level);
	}
	free_increment(incr);
	return (EXIT_SUCCESS);
}

int	get_number_of_commands(t_shell *shell)
{
	t_tok	*temp;
	int		nb_of_cmd;

	nb_of_cmd = 1;
	temp = shell->user_command->start;
	while (temp)
	{
		if (ft_strncmp(temp->var, "|", 2) == 0 && temp->quote == 0)
			nb_of_cmd++;
		temp = temp->next;
	}
	return (nb_of_cmd);
}
