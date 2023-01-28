/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:52:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/28 09:36:47 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_shell
{
	struct s_chained	*env_l;
	const char			*prompt;
	const char			*dir_path;
	char				*line_readed;
	char				**builtin_args;

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
