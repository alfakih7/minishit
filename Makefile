NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3
# READLINE = -I/Users/$(USER)/homebrew/opt/readline/include -L/Users/$(USER)/homebrew/opt/readline/lib
LIBFT = ./libft/libft.a

SRC =	parsing.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		quotes.c\
		check.c\
 
OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -l readline

$(LIBFT):
	@make all -C ./libft

clean :
	@make clean -C ./libft
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	@make fclean -C ./libft

re : fclean all