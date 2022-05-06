#ifndef LEXER_H
# define LEXER_H

#include "libft/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

char **split_args(char *line);

#endif
