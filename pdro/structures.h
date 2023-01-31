/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:52:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/30 13:27:49 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_shell
{
	struct s_chained	*env_l;
	struct s_chained	*sorted_env_l;
	const char			*prompt;
	const char			*dir_path;
	char				*line_readed;
	struct s_toklst		*user_command;

}				t_shell;

typedef struct s_node
{
	struct s_node		*prev;
	char				*variable;
	struct s_node		*next;
}				t_node;

typedef struct s_chained
{
	struct s_node		*start;
	int					nb_elem;
	struct s_node		*end;
}				t_chained;

typedef struct s_tok
{
	struct s_tok		*prev;
	char				*var;
	int			quote;
	struct s_tok		*next;
}				t_tok;

typedef struct s_toklst
{
	struct s_tok		*start;
	int					nb_elem;
	struct s_tok		*end;
}				t_toklst;

#endif