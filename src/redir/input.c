/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:45:56 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 20:13:15 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	input(t_main *mini, char *args)
{
	mini->in = open(args, O_RDONLY, S_IRWXU);
	if (mini->in == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(args, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->in, STDIN);
}

int	check_files(char **after_sep, t_main *main)
{
	if (ft_str_arr_len(after_sep) == 0)
	{
		ft_putstr_fd("bash$ ", STDERR);
		ft_putendl_fd("syntax error near unexpected token `newline'", STDERR);
		return (1);
	}
	if (ft_str_arr_len(after_sep) == 1)
		input(main, after_sep[0]);
	else if (ft_str_arr_len(after_sep) == 2)
		input(main, after_sep[1]);
	else
		return (-1);
	return (0);
}

void	execute_in_input(t_main *main, char **env, t_bt *bts, char **before_sep)
{
	execute(before_sep, main, env, bts);
	ft_close(main->in);
	dup2(main->fd_in, STDIN);
}

void	inpyt_cycle(t_main *main, char **env, t_bt *bts, char **before_sep)
{
	int	i;

	i = 1;
	while (i < ft_str_arr_len(main->after_sep) && !main->no_exec)
	{
		input(main, main->after_sep[i]);
		if (!main->no_exec)
		{
			execute(before_sep, main, env, bts);
			ft_close(main->in);
			g_exit_status = 1;
		}
		i++;
	}
	dup2(main->fd_in, STDIN);
	return ;
}

void	make_input(t_main *main, char **env, t_bt *bts, t_hash *cmd)
{
	char	**before_sep;
	char	**after_sep;
	t_hash	*tmp;

	tmp = cmd;
	after_sep = after_sep_func(tmp);
	before_sep = before_sep_func(tmp);
	main->no_exec = 0;
	if (check_files(after_sep, main) == 1 && !main->no_exec)
		return (clean_seps(after_sep, before_sep));
	else if (!main->no_exec && (check_files(after_sep, main) == 0))
		execute_or_exit(main, env, bts, before_sep);
	else
	{
		main->after_sep = after_sep;
		inpyt_cycle(main, env, bts, before_sep);
	}
	if (main->no_exec)
		g_exit_status = 1;
	clean_seps(after_sep, before_sep);
}
