/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:19 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/05 20:06:45 by ysachiko         ###   ########.fr       */
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
	int				key;
	char			*value;
	struct s_hash	*next;
	struct s_hash	*prev;
}	t_hash;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	char	*line;
	int		current_symbol;
	int		free_quote_flag;
	int		in_double_quots;
	int		in_single_quots;
	t_hash	*hash_head;
	t_hash	*tmp;
	t_env	*env_list;
}	t_main;

void	parser(t_main *main);
/*
LISTS
*/
t_hash	*ft_lstnew_hash(int key, void *value);
t_hash	*ft_lstlast_hash(t_hash *lst);
void	ft_lstadd_back_hash(t_hash **lst, t_hash *new);
/*
 USAGE FUNCTIONS
*/
int		is_space(char c);
int		is_single_quote(char c);
int		is_double_quote(char c);
char	*str_realloc(char *str);
void	str_add_new_symbol(char *str, char symbol);
/*
DEBUG_SHIT
*/
void	debug_print_list(t_hash *head);
void	debug_print_list_2(t_env *head);
/*
LEXER_MAIN_USAGE
*/
void	scip_space(t_main *main, int counter);
int		extend_string(char **argument, char symbol, int counter);
int		is_builtin(char *str);
int		parse_lexer_list(t_hash *head);
/*
ENV_INIT
*/
int		init_env(t_main *env_list_head, char **env);
char	*find_path(t_env *head);
char	*take_env_key(char *str);
char	*take_env_value(char *str);
t_env	*find_key_node(char *str, t_env *head);
/*
PARSE_ENV
*/
int		parse_env(t_main *main, t_hash *head);
void	env_str_refactor(t_main *main, t_hash *hash);
int		str_refactor(t_main *main, t_hash *hash, int i);
int		arg_str_refactor(t_main *main, t_hash *hash, int i);
char	*find_env(char *str, int i);
/*
PARSE ENV USAGE
*/
int		env_arg_len(char *str, int i);
void	str_env_pars(t_main *main, char **str);
void	set_empty_arg(t_hash *hash, int i, char *arg);
char	*get_str_after_arg(t_hash *hash, int i, char *arg);
char	*get_str_before_arg(t_hash *hash, int i);
char	*find_env(char *str, int i);
/*
PARSER USAGE
*/
int		is_spec_symbol(char c);
void	str_delete_symbol(t_hash *hash, int i);
/*
QUOTS
*/
char	*take_single_quote_arg(t_main *main, int counter);
char	*return_double_quotes(t_main *main, int counter);
char	*take_double_quote_args(t_main *main, int counter);
void	refactor_double_quote_arg(t_main *main, int counter, char **argument);
void	refactor_single_quote_arg(t_main *main, int counter, char **argument);

#endif
