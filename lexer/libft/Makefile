NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC = ft_striteri.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c \
	  ft_strlcat.c ft_strchr.c ft_strcmp.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	  ft_isalnum.c ft_isascii.c ft_isspace.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

SRC_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	  	ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ   = $(patsubst %.c,%.o,$(SRC))

OBJ_B = $(patsubst %.c,%.o,$(SRC_B))

D_FILES = $(patsubst %.c,%.d,$(SRC) $(SRC_B))

all: $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $?

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

bonus: 
	@make OBJ="$(OBJ) $(OBJ_B)" all

clean:
	$(RM) $(OBJ) $(OBJ_B) $(D_FILES)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
