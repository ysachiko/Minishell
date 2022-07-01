# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 17:55:47 by kezekiel          #+#    #+#              #
#    Updated: 2022/07/01 15:47:00 by ysachiko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror 

INC = includes/parser.h libft/libft.h

SRC	=	src/main/execute.c		src/main/main.c		src/main/builtins.c		src/main/pipe.c		src/main/signals.c \
		src/env/init_env.c \
		src/parser/parser.c							src/parser/list/list_head.c					src/parser/usage/check_add_realloc.c \
		src/parser/usage/debug_shit.c				src/parser/usage/lexer_main_usage.c			src/parser/cmd_utils.c \
		src/parser/usage/parse_env.c				src/parser/usage/parse_env_usage.c 			src/parser/usage/parse_str_env.c \
		src/parser/usage/parser_usage.c				src/parser/quots.c 							src/parser/list_refactor.c \
		src/parser/current_cmd.c \
		src/utils/free.c		src/utils/utils.c	src/utils/utils2.c		src/utils/utils3.c	src/utils/inits.c \
		builtins/sh_echo.c		builtins/sh_exit.c	builtins/sh_unset.c		builtins/sh_cd.c	builtins/sh_stuff.c \
		builtins/sh_export.c \
		src/redir/redir.c		src/redir/redir_usage.c						src/redir/input.c \
		src/redir/output.c		src/redir/append.c							src/redir/heredoc.c  \

OBJ = $(patsubst %.c,%.o,$(SRC))

LIBFT = libft

FLAGS = -L $(LIBFT) -lft

RDLN = -L /Users/yurakovalev/.brew/Cellar/readline/8.1.2/lib -I /Users/yurakovalev/.brew/Cellar/readline/8.1.2/include/ -lreadline

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@echo "\033[0;33m\n\nCompiling minishell..."
	@$(CC) $(CFLAGS) $(OBJ) $(RDLN) $(FLAGS) -o $(NAME)
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
