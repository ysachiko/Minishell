/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:40:08 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/30 16:51:08 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_line(char **after_sep)
{
	if (ft_str_arr_len(after_sep) == 0)
	{
		ft_putstr_fd("bash$ ", STDERR);
		ft_putendl_fd("syntax error near unexpected token `newline'", STDERR);
		return (1);
	}
	return (0);
}

int	checker(char **after_sep, t_main *main, char *name)
{
	if (ft_str_arr_len(after_sep) == 0)
	{
		ft_putstr_fd("bash$ ", STDERR);
		ft_putendl_fd("syntax error near unexpected token `newline'", STDERR);
		return (1);
	}
	if (ft_str_arr_len(after_sep) == 1)
		input(main, name);
	else
		return (-1);
	return (0);
}

void	heredoc(char *stop, char *name)
{
	char	*line;
	int		fd;

	fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0644);
	//if (fd < 0)
	line = readline("heredoc>");
	while (ft_strcmp(line, stop) != 0)
	{
		line = ft_strjoin(line, "\n");
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline("heredoc>");
	}
	close(fd);
	free(line);
}

void	make_heredoc(t_main *main, char **env, t_bt *bts, t_hash *cmd)
{
	char	**before;
	char	**after;
	char	*name;
	t_hash	*tmp;

	name = "tmpfile";
	tmp = cmd;
	after = after_sep_func(tmp);
	before = before_sep_func(tmp);
	main->no_exec = 0;
	if (check_line(after) == 1 && !main->no_exec)
		return (clean_seps(after, before));
	heredoc(after[0], name);
	if (!main->no_exec && (checker(after, main, name) == 0))
		execute_or_exit(main, env, bts, before);
	else
	{
		main->after_sep = after;
		input_cycle(main, env, bts, before);
	}
	if (name)
		unlink(name);
	if (main->no_exec)
		g_exit_status = 1;
	clean_seps(after, before);
}
