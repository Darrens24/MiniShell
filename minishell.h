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

/***\	BUILTINS	\***/

int			is_builtin_command(t_shell *shell);

//************* Directory

int					execute_directory_cmd(t_shell *shell);
int	    			print_pwd_linux(void);
int					change_directory(const char *path);

//************* Env

int					execute_builtin_cmd(t_shell *shell);
int					print_export(t_shell *shell);
int					add_env_variable(t_shell *shell);

//************* Echo

int					print_echo(t_shell *shell);
int					echo_parsing(t_shell *shell);

/***\	COMMANDS	\***/

int			command_manager(t_shell *shell, char **envp);
int			execute_command(t_shell *shell, char **envp);
char		**get_array_command(t_shell *shell);

//********>> Path

char		*get_path(char **envp);
char		*get_correct_path(t_shell *shell);

//********>> Pipe

int			execupe_pipe_command(t_shell *shell, char **envp);

/***\	LISTS	\***/

t_chained	*new_front_node(t_chained *list, char *line);
t_chained	*new_back_node(t_chained *list, char *line);
t_chained	*remove_front_node(t_chained *list);
t_chained	*remove_back_node(t_chained *list);
t_node		*go_to_end(t_chained *list);
t_node		*remove_current_node(t_node *node, t_chained *lst);

/***\	LIST UTILS	\***/

int			is_empty(t_chained *list);
t_chained	*null_list(void);
void		print_list(t_chained *list);
t_chained	*sort_list(t_chained *list);

/***\	UTILS	\***/

char		*ft_strndup(char *line, int start, int end);

/***\	SIGNALS UTILS   \***/

void		handler(int num);

/***\      TOKEN MANAG     \***/

int			is_emptytok(t_toklst *list);
t_toklst	*new_back_tok(t_toklst *tokenlst, char *line, int start, int end);
t_toklst	*remove_back_tok(t_toklst *list);
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
