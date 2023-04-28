/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:34:22 by eleleux           #+#    #+#             */
/*   Updated: 2023/04/28 09:23:19 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BLK "\e[0;90m"
# define RED "\e[0;91m"
# define GRN "\e[0;92m"
# define YEL "\e[0;93m"
# define BLU "\e[0;94m"
# define MAG "\e[0;95m"
# define CYN "\e[0;96m"
# define WHT "\e[0;97m"

# define TRUE 1
# define FALSE 0
# define DOT "filename argument required\n.: usage: . filename [arguments]\n"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <string.h>
# include <stdint.h>
# include "./Libft/libft.h"
# include "structures.h"

extern int	g_err;

/***\	READLINE	\***/

void		rl_replace_line(const char *text, int clear_undo);

/***\	DATA	\***/

int			allocate_shell(t_shell *shell, char **envp);
int			initialize_variables(t_shell *shell);
int			increment_sh_level(t_shell *shell);
int			clean_memory(t_shell *shell);
int			free_array(char **array);
char		**get_array_env(t_shell *shell);
void		clear_chained_lst(t_chained *lst);
int			free_increment(t_increment *incr);
int			clean_between_cmds(t_shell *shell);

/***\	BUILTINS	\***/

int			is_builtin_command(t_shell *shell, int index);
int			builtin_manager(t_shell *shell, int index);
int			exit_shell(t_shell *shell);

//************* Directory

char		*get_home(char **array_env);
int			go_to_home_directory(t_shell *shell);
int			go_to_previous_directory(t_shell *shell);
int			execute_directory_cmd(t_shell *shell, int i);
int			print_pwd_linux(t_shell *shell);
int			change_directory(t_shell *shell, const char *path);
int			update_pwd(t_shell *shell, t_chained *list);
int			update_oldpwd(t_shell *shell, t_chained *list);

//************* Env

int			execute_builtin_cmd(t_shell *shell, int i);
int			export_manager(t_shell *shell, int i);
int			add_env_variable(t_shell *shell);
int			fill_basic_env(t_shell *shell);
int			envchecker(char *line, t_chained *env);
int			envindex(char *line, t_chained *env);

//************* Export

int			equal_in_string(char *str);
t_tok		*find_export_args(t_shell *shell);
int			export_ascii_sorted(t_tok *temp, t_chained *sorted_env);
int			export_variable(t_shell *shell);
void		put_quotes_to_export(char *variable);
int			print_export(t_shell *shell);

//************* Unset

int			valid_arg(char *arg);
t_tok		*find_unset_args(t_shell *shell);
t_node		*find_node_to_remove(char *var_before_equal, t_chained *lst);
int			clean_export_list(t_shell *shell, char *temp3,
				t_node *temp, t_node *temp2);
int			unset_variable(t_shell *shell);

//************* Echo

int			print_echo(char **command, t_shell *shell);

/***\	COMMANDS	\***/

int			command_manager(t_shell *shell, char **envp);
int			execute_command(t_shell *shell, char **envp);
char		**get_array_command(t_shell *shell);
int			get_number_of_commands(t_shell *shell);
int			get_number_of_pipes(t_shell *shell);
char		**get_command_in_tok(t_shell *shell, int index);

//************* Path

char		*find_path(int index, t_shell *shell);
char		*get_path(char **array_env);
char		*get_correct_path(t_shell *shell, int index);

//************* Pipe

int			slash_manager(t_shell *shell, int index);
int			get_array_cmd_and_pipe_fds(t_shell *shell);
int			pipe_command(t_shell *shell);
int			execute_execve(t_shell *shell, char *temp,
				struct stat buff, int index);

//************************** Pipe Utils

int			close_fds(int *fd);
int			wait_pids(int *pid, t_shell *shell);
t_tok		*go_to_next_operator(t_shell *shell, t_tok *tok, int index);
int			early_out_redirection(int *fd);
int			inside_redirection(int *fd);
void		free_pids_fds(t_shell *shell);

/***\	REDIRECTION	\***/

int			infile_redirection(t_shell *shell, t_tok *temp);
int			heredoc_redirection(t_shell *shell, t_tok *temp);
int			outfile_redirection(t_shell *shell, t_tok *temp);
int			append_redirection(t_shell *shell, t_tok *temp);
int			heredoc_dup(t_shell *shell);

//************* Redirection Parsing

int			redirection_parsing(t_shell *shell, int index);
int			infile_redirection_parsing(t_shell *shell);
int			outfile_redirection_parsing(t_shell *shell);

//************* Redirection Utils

int			is_infile_redirection(t_toklst *user_command);
int			is_outfile_redirection(t_toklst *user_command);
char		*append_newline(char *limiter);
int			delete_operator_and_infile(t_shell *shell);
int			delete_operator_and_outfile(t_shell *shell);

/***\	LISTS	\***/

t_chained	*new_front_node(t_chained *list, char *line);
t_chained	*new_back_node(t_chained *list, char *line);
t_chained	*remove_front_node(t_chained *list);
t_chained	*remove_back_node(t_chained *list);
t_node		*remove_current_node(t_node *node, t_chained *lst);
t_chained	*new_current_node(t_chained *lst, int index, char *variable);

//************* Lists Utils

int			is_empty(t_chained *list);
t_chained	*null_list(void);
void		print_list(t_chained *list);
t_chained	*sort_list(t_chained *list);
t_node		*go_to_end(t_chained *list);

/***\	SIGNALS UTILS   \***/

void		handler(int num);
void		heredoc_handler(int num);
void		remove_ctrlc(int mode);
void		do_nothing(int num);
int			reset_echo(void);
int			error_func(int error_code);

/***\      TOKEN MANAG     \***/

int			is_emptytok(t_toklst *list);
t_toklst	*new_back_tok(t_toklst *tokenlst, char *line, int start, int end);
t_toklst	*remove_back_tok(t_toklst *list);
t_toklst	*remove_front_tok(t_toklst *list);
t_tok		*remove_current_tok(t_tok *tok, t_toklst *list);
void		print_toklst(t_toklst *list);
void		clear_toklst(t_toklst *lst);

/***\      UTILS           \***/

char		*ft_strndup(char *line, int start, int end);
int			ft_strlenequal(char *line);
int			argument_after_cmd(t_shell *shell);
int			option_n(char **command, int i);
int			option_njump(char **command, int i);

/***\      PARSING UTILS   \***/

int			is_wspace(char c);
int			is_sep(char c);
int			jump_wspace(char *line, int i);
int			checknextquote(char *line, char quote, int start);
int			errorintoken(t_toklst *tokenlst, char *error);

/***\      PARSING         \***/

void		token_parsing(t_toklst *tokenlst, char *line);

/***\      TOKENISATION		\***/

char		*dquoteparser(t_tok *token, int i, char *newvar, t_chained *env);
int			dquotejumper(t_tok *token, int i);
int			tokenisation(t_toklst *tokenlst, t_chained *env);
char		*squoteparser(t_tok *token, int i, char *newvar);
int			squotejumper(t_tok *token, int i);
t_toklst	*new_back_tok_q(t_toklst *tokenlst, char *line, int start, int end);
int			token_checker(t_shell *shell);
char		*ft_strjointok(char const *s1, char const *s2);
void		dollarcase(t_tokation *tk, t_chained *env);
void		norm_errors(t_tokation *tk, t_toklst *tokenlst);
void		antislash_norm(t_tokation *tk, t_chained *env);
void		tilde_and_classicnorm(t_tokation *tk, t_chained *env);
char		*join_without_leaks(char *newvar, char *temp);
char		*join_without_leaks2(char *newvar, char *temp);

//************************** Token Utils

char		*envfinder(char *line, char *newvar, t_chained *env);
char		*envvarparser(t_tok *token, int i, char *newvar, t_chained *env);
int			envvarjumper(t_tok *token, int i);
char		*vagueparser(int i, char *newvar, t_chained	*envp);
void		token_norm_parsing(t_tokation *tk, t_chained *env);
char		*get_command(t_shell *shell, int index);

#endif
