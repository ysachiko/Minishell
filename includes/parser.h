/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:19 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/24 17:00:46 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// ERRORS
# define ERROR_EXEC_BIN_INIT "Error: malloc in execute binaty cmd\n"
# define ERROR_PARS_ENVP_PATH "Error: parsing ENVP PATH\n"
# define ERROR_NO_BINARY_FILE "Error: binary file not exist\n"

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
	int		end_flag;
	t_hash	*current_cmd;
	t_hash	*tmp2;
	t_hash	*hash_head;
	t_hash	*tmp;
	t_env	*env_list;
}	t_main;

void	rl_replace_line(const char *text, int clear_undo);
void	parser(t_main *main);
void	make_lexer(t_main	*main);
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
void	set_empty_arg(t_hash *hash, int i, char *arg);
char	*get_str_after_arg(t_hash *hash, int i, char *arg);
char	*get_str_before_arg(t_hash *hash, int i);
char	*find_env(char *str, int i);
/*
PARSER USAGE
*/
int		is_spec_symbol(char c);
void	str_delete_symbol(t_hash *hash, int i);
void	set_double_quote_flag_value(t_main *main);
void	set_single_quote_flag_value(t_main *main);
int		symbol_check(t_main *main, int counter);
/*
QUOTS
*/
char	*take_single_quote_arg(t_main *main, int counter);
char	*return_double_quotes(t_main *main, int counter);
char	*take_double_quote_args(t_main *main, int counter);
void	refactor_double_quote_arg(t_main *main, int counter, char **argument);
void	refactor_single_quote_arg(t_main *main, int counter, char **argument);
/*
LIST REFACTOR
*/
void	refactor_list(t_hash *hash, t_main *main);
void	refactor_double_quote_arg_2(t_main *main, int counter, char **argument);
void	refactor_single_quote_arg_2(t_main *main, int counter, char **argument);
char	*take_simple_argument_2(t_main *main, int counter);
void	refactor_simple_arg_2(t_main *main, int counter, char **argument);
/*
PARSE_STR_ENV
*/
void	realloc_argument(char **arg, char *tmp);
void	str_env_pars(t_main *main, char **str);
void	ft_return_quots(char *tmp, char **argument, t_main *main);
/*
FREE
*/
void	clean_env_node(t_env *envp);
void	free_split(char **split);
void	clean_env(t_env *envp);
void	free_hash(t_hash *head);
void	end_prog(char *err, int code, int mode);
/*
UTILS
*/
char	**list_parser(t_hash *head);
int		check_export(char *s);
t_env	*search_env(t_env *head, char *key);
t_env	*new_env(char *key, char *value);
void	add_env(t_env **env, t_env *new);
t_env	*env_last(t_env *head);
t_env	*copy_env(t_env *head);
void	sort_env(t_env *copy);
char	**hash_parser(t_hash *head);
int		lst_size(t_hash *lst);
/*
EXECUTE
*/
int		execute(char **args, t_main *all, char **env);
int		launch(char **args, t_main *all, char **env);
char	**path_parser(t_env *all);
char	*env_path(char **paths, char *cmd);
char	*search_paths(char **paths, char *cmd);
/*
BUILT-INS
*/
/*
char *builtins[] = {"cd", "exit", "pwd", "env", "export", "unset", "echo"};
int (*built[]) (char **, t_main *) = {&sh_cd, &sh_exit, &sh_pwd, &sh_env, &sh_export, &sh_unset, &sh_echo};
*/
int		num_builtins();
int		sh_unset(char **args, t_main *all);
int		sh_export(char **args, t_main *all);
int		sh_cd(char **args, t_main *all);
int		sh_exit(char **args, t_main *all);
int		sh_pwd(char **args, t_main *all);
int		sh_env(char **args, t_main *all);
/*
ECHO
*/
int		sh_echo(char **argv, t_main *all);

#endif
