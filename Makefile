NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  	data.c \
	  	list_manip.c \
		list_utils.c \
		dirmanagement.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./Libft
	$(CC) $(CFLAGS) -I ./ -LLibft -lft $(SRC) -o $@ ./Libft/libft.a -lreadline

clean:
	rm -f $(OBJ)
	@make clean -C ./Libft

fclean:	clean
	rm -f $(NAME)
	@make fclean -C ./Libft

re:	fclean all

