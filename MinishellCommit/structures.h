/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:52:52 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/18 15:15:14 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_shell
{
	struct s_chained	*env_l;
	char				**array_env;
	struct s_chained	*sorted_env_l;
	char				*home;
	const char			*prompt;
	char				*current_dir_path;
	char				*previous_dir_path;
	char				*line_readed;
	struct s_toklst		*user_command;
	char				**all_path;
	char				*correct_path;
	char				**array_command;
	char				***multi_cmd;
	int					infile;
	char				*buffer_doc;
	char				*limiter_doc;
	pid_t				*pid;
	int					**fd;
	int					doc_fd[2];
	int					outfile;
	int					append;
	int					saved_stdin;
	int					saved_stdout;
	int					out;
	char				**ls_cmd;
	int					nb_of_sub;
	char				*wild_before;
	char				**wild_middle;
	char				*wild_after;
	int					increment;
	pid_t				here;
	struct s_tokation	*tkion;	
	struct s_cmdlst		*cmdlst;
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
	int					quote;
	struct s_tok		*next;
}				t_tok;

typedef struct s_toklst
{
	struct s_tok		*start;
	int					nb_elem;
	struct s_tok		*end;
}				t_toklst;

typedef struct s_increment
{
	t_node				*temp;
	char				*sh_level;
	int					sh;
	char				*itoa_sh;
	char				*new_sh_level;
	int					i;
}				t_increment;

typedef struct s_cmd
{
	struct s_cmd		*prev;
	char				**var;
	int					exec;
	int					prio;
	struct s_cmd		*next;
}				t_cmd;

typedef struct s_cmdlst
{
	struct s_cmd		*start;
	int					nb_elem;
	struct s_cmd		*end;
}				t_cmdlst;

typedef struct s_tokation
{
	t_tok				*elem;
	int					i;
	char				*newvar;
	int					start;
	char				*temp;
}				t_tokation;

typedef struct	s_op
{
	struct s_op		*prev;
	struct s_cmdlst	*cmdlst;
	struct s_op		*next;
}				t_op;

typedef struct	s_oplst
{
	struct s_op		*start;
	int				nb_elem;
	struct s_op		*end;
}				t_oplst;

typedef struct s_branch
{
	struct s_branch	*right;
	struct s_branch	*left;
	char			**cmd;
}				t_branch;

typedef struct s_tree
{
	struct s_branch	*start; 
	int				nb_elem;
}				t_tree;

#endif
