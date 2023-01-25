#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_shell
{
	struct s_chained	*env_l;
	const char			*prompt;
	char				*line_readed;

}				t_shell;

//	DATA	//

int			allocate_shell(t_shell *shell, char **envp);
int			clean_leaks(t_shell *shell);

//	LISTS	//

t_chained	*new_front_node(t_chained *list, char *line);
t_chained	*new_back_node(t_chained *list, char *line);
t_chained	*remove_front_node(t_chained *list);
t_chained	*remove_back_node(t_chained *list);
t_node		*go_to_end(t_chained *list);

//	LISTS UTILS	//

int			is_empty(t_chained *list);
t_chained	*null_list(void);
void		print_list(t_chained *list);

//	DIRECTORY	//

void		print_cwd_linux(void);
void		print_cwd_mac(void);
void    	print_pwd_linux(void);

//	DIRECTORY	//

void red(void);
void cyan(void);
void green(void);
void yellow(void);
void reset(void);

#endif
