# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almohame <almohame@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 17:14:53 by asid-ahm          #+#    #+#              #
#    Updated: 2024/07/06 07:11:11 by almohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
YELLOW = "\033[0;33m"
RESET = "\033[0m"

CC = cc
# CFLAGS = -Wall -Werror -Wextra -I.
CFLAGS = -I.

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCDIR = BSRC
OBJDIR = BOBJ
NAME = minishell
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)
	@echo $(GREEN_B)"\n$(NAME) is Compiled.🐢 \n"$(RESET)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L$(LIBFT_DIR) -lft 

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo $(YELLOW)".\c"$(RESET)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean
	@echo $(YELLOW)"Cleaned"$(RESET)

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo $(YELLOW)"Fully cleaned"$(RESET)

re: fclean all

.PHONY: all bonus clean fclean re
