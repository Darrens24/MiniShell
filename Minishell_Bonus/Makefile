# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 10:28:45 by eleleux           #+#    #+#              #
#    Updated: 2023/05/10 10:09:05 by eleleux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOCOLOR='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LIGHTGRAY='\033[0;37m'
DARKGRAY='\033[1;30m'
LIGHTRED='\033[1;31m'
LIGHTGREEN='\033[1;32m'
YELLOW='\033[1;33m'
LIGHTBLUE='\033[1;34m'
LIGHTPURPLE='\033[1;35m'
LIGHTCYAN='\033[1;36m'
WHITE='\033[1;37m'

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRC = data/data.c \
		data/free.c \
		data/path.c \
		data/commands.c \
		data/errors_bonus.c \
		utils.c \
		lists/list_manip.c \
		lists/list_manip2.c \
		lists/list_utils.c \
		builtins/dir_management.c \
		builtins/dir_utils.c \
		builtins/env_management.c \
		builtins/env_utils.c \
		builtins/export.c \
		builtins/export_unset.c \
		builtins/unset.c \
		signals.c \
		tokens/token_management.c \
		tokens/token_management2.c \
		tokens/token_utils.c \
		tokens/token_utils2.c \
		tokens/tokenisation.c \
		tokens/token_checker.c \
		tokens/quotes_management2.c \
		tokens/quotes_management.c \
		tokens/token_wildcard.c \
		parsing/parsing_utils.c \
		parsing/parsing.c \
		execution/exec/pipe.c \
		execution/exec/pipe_utils.c \
		execution/exec/execute_execve.c \
		redirections/heredoc.c \
		redirections/redirections.c \
		redirections/redirection_parsing.c \
		redirections/redirection_utils.c \
		wildcards/wildcards_utils.c \
		wildcards/wildcards_data.c \
		wildcards/wildcards_parsing.c \
		wildcards/wildcards.c \
		tree/tree.c \
		tree/tree_construction.c \
		tree/branch_creation.c \
		tree/parentheses.c \
		tree/tree_data.c \
		tree/tree_data2.c \
		tree/tree_utils.c \
		tree/parentheses_jump.c \
		tree/token_tree.c \
		execution/exec_bonus/execution_bonus.c \
		execution/exec_bonus/clean_tree.c \
		execution/exec_bonus/execution_utils.c \
		execution/exec_bonus/execute_final_boss.c \
		execution/exec_bonus/subshell.c \
		execution/exec_bonus/execution_bonus_utils.c \
		execution/exec_bonus/path_bonus.c \
		execution/exec_bonus/direction_execute.c \
		bonusbuiltin/builtin_bonus.c \
		bonusbuiltin/dir_management_bonus.c \
		bonusbuiltin/dir_utils_bonus.c \
		bonusbuiltin/env_management_bonus.c \
		bonusbuiltin/env_utils_bonus.c \
		bonusbuiltin/export_bonus.c \
		bonusbuiltin/unset_bonus.c \
		main.c \


OBJ = $(SRC:.c=.o)

#NORM = $(shell norminette | grep Error: | wc -l | awk '{print $1}')
#NORMINETTE = $(shell ls | grep ewhjgewjhghewji | wc -l | awk '{print $1}')

#ifeq (${NORM}, ${NORMINETTE})
#    NORMINETTE = "${WHITE}NORM : ${GREEN}OK${NOCOLOR}\n"
#else
#    NORMINETTE = "${WHITE}NORM : ${RED}${NORM}errors${NOCOLOR}\n"
#endif

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@echo ${LIGHTBLUE}Libft Compiling... !${NOCOLOR}
	@make -C ./Libft
	@echo ${LIGHTBLUE}Minishell Compiling... !${NOCOLOR}
	@$(CC) $(CFLAGS) -LLibft -lft $(OBJ) -o $@ ./Libft/libft.a -L ~/.brew/opt/readline/lib -lreadline -I ~/.brew/opt/readline/include/readline
	@echo ${LIGHTGREEN}Minishell Compiled !${NOCOLOR}
	@echo ${NORMINETTE}

clean:
	@make clean -C ./Libft
	@echo ${LIGHTRED}Libft Objects Removed !${NOCOLOR}
	@rm -f $(OBJ)
	@echo ${LIGHTRED}Minishell Objects Removed !${NOCOLOR}

fclean:	clean
	@make fclean -C ./Libft
	@rm -f $(NAME)
	@echo ${LIGHTRED}Minishell Removed !${NOCOLOR}

re:	fclean all

