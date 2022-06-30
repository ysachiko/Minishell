/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:08:31 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 18:33:12 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	output(t_main *main, char **after_arg)
{
	main->out = open(after_arg[0], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (main->out == -1)
	{
		ft_putstr_fd("bash$ ", STDERR);
		ft_putstr_fd(after_arg[0], STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		main->no_exec = 1;
		return ;
	}
	dup2(main->out, STDOUT);
}

void	make_output(t_main *main, char **env, t_bt *bts, t_hash *cmd)
{
	char	**before_sep;
	char	**after_sep;
	t_hash	*tmp;
	int		i;

	tmp = cmd;
	i = 1;
	after_sep = after_sep_func(tmp);
	before_sep = before_sep_func(tmp);
	main->no_exec = 0;
	output(main, after_sep);
	execute(before_sep, main, env, bts);
	ft_close(main->out);
	dup2(main->fd_out, STDOUT);
	clean_seps(after_sep, before_sep);
}
