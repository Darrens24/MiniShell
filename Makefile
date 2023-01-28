# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eleleux <eleleux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 10:28:45 by eleleux           #+#    #+#              #
#    Updated: 2023/01/28 10:36:33 by eleleux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
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

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  	data.c \
	  	list_manip.c \
		list_utils.c \
		dirmanagement.c \
		envmanagement.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)

$(NAME): $(OBJ)
	@echo ${ORANGE}Libft Compiling... !${NOCOLOR}
	@make -C ./Libft
	@echo ${ORANGE}Minishell Compiling... !${NOCOLOR}
	@$(CC) $(CFLAGS) -I ./ -LLibft -lft $(OBJ) -o $@ ./Libft/libft.a -lreadline
	@echo ${GREEN}Minishell Compiled !${NOCOLOR}

clean:
	@make clean -C ./Libft
	@rm -f $(OBJ)
	@echo ${LIGHTPURPLE}Minishell Objects Removed !${NOCOLOR}

fclean:	clean
	@make fclean -C ./Libft
	@rm -f $(NAME)
	@echo ${RED}Minishell Removed !${NOCOLOR}

re:	fclean all

