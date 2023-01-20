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

typedef struct s_shell
{
	char		*line_from_prompt;
	const char	*prompt;

}				t_shell;

typedef struct s_history
{
	char	*user_command;
	char	*next;
}				t_history;

#endif

//	DATA	//

int		allocate_data(t_shell *shell);
int		clean_leaks(t_shell *shell);
