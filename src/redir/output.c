/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:08:31 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/30 20:36:12 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	werror_killer(int ac, char **av)
{
	(void) ac;
	(void) av;
}

void	output(t_main *main, char **after_arg)
{
	if (after_arg[0] == NULL)
	{
		ft_putstr_fd("bash: ", STDERR);
		ft_putendl_fd("syntax error near unexpected token `newline'", STDERR);
		main->no_exec = 1;
		g_exit_status = 258;
		return ;
	}
	main->out = open(after_arg[0], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (main->out == -1)
	{
		ft_putstr_fd("bash: ", STDERR);
		ft_putstr_fd(after_arg[0], STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		main->no_exec = 1;
		return ;
	}
	dup2(main->out, STDOUT);
}

void	make_output(t_main *main, t_hash *cmd)
{
	char	**before_sep;
	char	**after_sep;
	t_hash	*tmp;
	int		i;

	tmp = cmd;
	i = 1;
	after_sep = after_sep_func(tmp);
	before_sep = before_sep_func(tmp);
	if (!after_sep[0] && !before_sep[0])
	{
		print_err("", "syntax error near unexpected token `newline'");
		g_exit_status = 2;
		return ;
	}
	output(main, after_sep);
	clean_seps(after_sep, before_sep);
}
