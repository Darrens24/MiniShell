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
# include <dirent.h>
# include <termios.h>
# include <string.h>
# include <stdint.h>
# include "./Libft/libft.h"
# include "structures.h"


/***\	DATA	\***/

int			allocate_shell(t_shell *shell, char **envp);
int			clean_memory(t_shell *shell);
int			free_array(char **array);
char		**get_array_env(t_shell *shell);
void		clear_chained_lst(t_chained *lst);
int			clean_between_cmds(t_shell *shell);

/***\	BUILTINS	\***/

int			is_builtin_command(t_shell *shell, int i);

//************* Directory

int					execute_directory_cmd(t_shell *shell, int i);
int	    			print_pwd_linux(void);
int					change_directory(const char *path);

//************* Env

int					execute_builtin_cmd(t_shell *shell, int i);
int					print_export(t_shell *shell);
int					add_env_variable(t_shell *shell);

//************* Echo

int					print_echo(t_shell *shell);
int					echo_parsing(t_shell *shell);

/***\	COMMANDS	\***/

int			command_manager(t_shell *shell, char **envp);
int			execute_command(t_shell *shell, char **envp);
char		**get_array_command(t_shell *shell);
int			get_number_of_commands(t_shell *shell);
char		**get_command_in_tok(t_shell *shell, int index);

//************* Path

char				*get_path(char **envp);
char				*get_correct_path(t_shell *shell, int index);

//************* Pipe

int					get_array_cmd_and_pipe_fds(t_shell *shell);
int					pipe_command(t_shell *shell);
int					redirect_and_execute_cmd(t_shell *shell, int index);

//************************** Pipe Utils

int							close_fds(int **fd);
int							wait_pids(int *pid);
t_tok						*go_to_next_pipe(t_shell *shell, t_tok *tok, int index);
int							early_out_redirection(int *fd);
int							inside_redirection(int *fd);
void						free_pids_fds(t_shell *shell);

/***\	REDIRECTION	\***/

int					infile_redirection(t_shell *shell);
int					heredoc_redirection(t_shell *shell);
int					outfile_redirection(t_shell *shell);
int					append_redirection(t_shell *shell);

//************************** Redirection Utils

int							is_infile_redirection(t_toklst *user_command);
int							is_outfile_redirection(t_toklst *user_command);
int							infile_redirection_parsing(t_shell *shell);
int							outfile_redirection_parsing(t_shell *shell);
char						*append_newline(char *limiter);
int							delete_operator_and_infile(t_shell *shell);
int							delete_operator_and_outfile(t_shell *shell);

/***\	LISTS	\***/

t_chained	*new_front_node(t_chained *list, char *line);
t_chained	*new_back_node(t_chained *list, char *line);
t_chained	*remove_front_node(t_chained *list);
t_chained	*remove_back_node(t_chained *list);
t_node		*go_to_end(t_chained *list);
t_node		*remove_current_node(t_node *node, t_chained *lst);

//************************** Lists Utils

int							is_empty(t_chained *list);
t_chained					*null_list(void);
void						print_list(t_chained *list);
t_chained					*sort_list(t_chained *list);

/***\	SIGNALS UTILS   \***/

void		handler(int num);

/***\      TOKEN MANAG     \***/

int			is_emptytok(t_toklst *list);
t_toklst	*new_back_tok(t_toklst *tokenlst, char *line, int start, int end);
t_toklst	*remove_back_tok(t_toklst *list);
t_toklst	*remove_front_tok(t_toklst *list);
void		print_toklst(t_toklst *list);
void		clear_toklst(t_toklst *lst);

/***\      UTILS           \***/

char		*ft_strndup(char *line, int start, int end);

/***\      PARSING UTILS   \***/

int			is_wspace(char c);
int			is_sep(char c);
int			jump_wspace(char *line, int i);
int			checknextquote(char *line, char quote, int start);
int			errorintoken(t_toklst *tokenlst, char *error);

/***\      PARSING         \***/

void		token_parsing(t_toklst *tokenlst, char *line);

/***\      TOKENISATION		\***/

void		tokenisation(t_toklst *tokenlst, t_chained *env);


#endif
