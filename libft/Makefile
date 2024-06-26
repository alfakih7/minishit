# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 08:06:54 by asid-ahm          #+#    #+#              #
#    Updated: 2024/06/03 08:18:25 by asid-ahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
YELLOW = "\033[0;33m"
RESET = "\033[0m"

CC = cc
AR = ar -rcs
CFLAGS = -Wall -Werror -Wextra

SRCDIR = SRC
OBJDIR = OBJ
NAME = libft.a
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


all: $(NAME)
	@-echo $(BLUE_I)"\n$(NAME) is Compiled.🐢 \n"$(RESET)

$(NAME): $(OBJECTS)
	@-$(AR) $(NAME) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@-mkdir -p $(OBJDIR)
	@-$(CC) $(CFLAGS) -c $< -o $@
	@-echo $(YELLOW)".\c"$(RESET)

clean:
	@-rm -rf $(OBJDIR)
	@-echo $(YELLOW)"Cleaned"$(RESET)

	
fclean: clean
	@-rm -rf $(NAME)
	@-echo $(YELLOW)"Fully cleaned"$(RESET)

re: fclean all

.PHONY: all clean fclean re
