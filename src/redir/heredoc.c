/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:40:08 by kezekiel          #+#    #+#             */
/*   Updated: 2022/07/01 15:56:18 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	init_new_value(t_main *main)
{
	main->no_exec = 0;
	main->echo = 0;
	main->cat = 0;
	if (!ft_strcmp(main->cur_md[0], "echo"))
		main->echo = 1;
	if (!ft_strcmp(main->cur_md[0], "cat"))
		main->cat = 1;
}

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

void	heredoc(char *stop, char *name, t_main *main)
{
	char	*line;
	char	*tmp;
	int		fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("heredoc>");
	while (line && ft_strcmp(line, stop) != 0)
	{
		tmp = ft_strjoin(line, "\n");
		write(fd, tmp, ft_strlen(tmp));
		free(line);
		free(tmp);
		line = readline("heredoc>");
	}
	input(main, name);
	if (main->pipin)
		dup2(main->pipin, STDOUT);
	close(fd);
	free(line);
}

void	make_heredoc(t_main *main, t_hash *cmd)
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
	heredoc(after[0], name, main);
	if (name)
		unlink(name);
	if (main->no_exec)
		g_exit_status = 1;
	clean_seps(after, before);
}
