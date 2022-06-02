/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:19 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/02 19:50:16 by ysachiko         ###   ########.fr       */
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

typedef struct s_env
{
	char	*arg;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	char	*line;
	int		current_symbol;
	t_env	*env_list;
}	t_main;

void	parser(t_main *main);
/*
LISTS
*/
t_hash	*ft_lstnew_hash(void *key, void *value);
t_hash	*ft_lstlast_hash(t_hash *lst);
void	ft_lstadd_back_hash(t_hash **lst, t_hash *new);
/*
 USAGE FUNCTIONS
*/
int		is_space(char c);
int 	is_single_quote(char c);
int		is_double_quote(char c);
char	*str_realloc(char *str);
void	str_add_new_symbol(char *str, char symbol);
/*
DEBUG_SHIT
*/
void	DEBUG_PRINT_LIST(t_hash *head);
void	DEBUG_PRINT_LIST_2(t_env *head);
/*
LEXER_MAIN_USAGE
*/
void	scip_space(t_main *main, int counter);
int		extend_string(char **argument, char symbol, int counter);
/*
ENV_INIT
*/
int		init_env(t_main *env_list_head, char **env);
char	*find_path(t_env *head);

#endif
