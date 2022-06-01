/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:19 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/01 19:28:14 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

typedef struct s_hash
{
	void	*key;
	void	*value;
	struct s_hash *next;
	struct s_hash *prev;
}	t_hash;

typedef struct s_main
{
	char	*line;
	int		current_symbol;
} t_main;


void	parser(t_main *main);
t_hash	*ft_lstnew_head(void *key, void *value);

#endif
