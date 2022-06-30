/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:45:56 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/30 20:33:58 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	input(t_main *mini, char *args)
{
	mini->in = open(args, O_RDONLY, S_IRWXU);
	if (mini->in == -1)
	{
		ft_putstr_fd("bash: ", STDERR);
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
		ft_putstr_fd("bash: ", STDERR);
		ft_putendl_fd("syntax error near unexpected token `newline'", STDERR);
		g_exit_status = 258;
		return (1);
	}
	if (main->echo)
		input(main, after_sep[0]);
	else if (main->cat && ft_str_arr_len(after_sep) > 1)
		input(main, after_sep[1]);
	else if (main->cat && ft_str_arr_len(after_sep) == 1)
		input(main, after_sep[0]);
	else if (!main->cat && !main->echo)
		input(main, after_sep[0]);
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

void	input_cycle(t_main *main)
{
	int	i;

	if (cur_sep(main->current_cmd) == HER)
		i = 1;
	else
		i = 0;
	while (i < ft_str_arr_len(main->after_sep) && !main->no_exec)
	{
		input(main, main->after_sep[i]);
		if (!main->no_exec)
		{
			g_exit_status = 1;
			break ;
		}
		i++;
	}
	return ;
}

void	make_input(t_main *main, t_hash *cmd)
{
	char	**before_sep;
	char	**after_sep;
	t_hash	*tmp;

	tmp = cmd;
	after_sep = after_sep_func(tmp);
	before_sep = before_sep_func(tmp);
	if (!after_sep[0] && !before_sep[0])
	{
		print_err("", "syntax error near unexpected token `newline'");
		g_exit_status = 2;
		return ;
	}
	if (check_files(after_sep, main) == 1 && !main->no_exec)
		return (clean_seps(after_sep, before_sep));
	else if (ft_str_arr_len(after_sep) > 2)
	{
		if (main->echo)
			input(main, after_sep[0]);
		if (main->cat)
			input(main, after_sep[1]);
		main->after_sep = after_sep;
	}
	if (main->no_exec)
		g_exit_status = 1;
	clean_seps(after_sep, before_sep);
}
