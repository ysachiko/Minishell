# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 17:55:47 by ysachiko          #+#    #+#              #
#    Updated: 2022/06/01 18:26:26 by ysachiko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minihell

CC = gcc

CFLAGS =

INC = includes/parser.h libft/libft.h

SRC	   = src/parser/lexer.c src/parser/parser.c  src/parser/list/list_head.c

OBJ = $(patsubst %.c,%.o,$(SRC))

LIBFT = libft

FLAGS = -L $(LIBFT) -lft

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@echo "\033[0;33m\n\nCompiling minishell..."
	@$(CC) $(CFLAGS) $(OBJ) $(FLAGS) -o $(NAME) -ledit
	@echo "\n\033[0;36mDone."

%.o : %.c $(INC)
	@printf "\033[0;34mGenerating minishell objects... %-10.10s\r" $@
	gcc $(CFLAGS) -c $< -o $@

clean :
	@make clean -C $(LIBFT)
	@echo "\033[0;31m\nDeleting objects..."
	rm -f $(OBJ)
	@echo "\n\033[0;31mDeleted.\n"

fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
