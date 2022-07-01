/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:34:04 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/30 21:09:55 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	**before_sep_func(t_hash *cmd)
{
	t_hash	*tmp_2;
	int		counter;
	char	**before_sep;

	counter = 0;
	tmp_2 = cmd;
	counter = ft_strlen_before_sep(cmd);
	before_sep = malloc(sizeof(char *) * (counter + 1));
	counter = 0;
	while (!(tmp_2->key > 2 && tmp_2->key < 7))
	{
		before_sep[counter] = ft_strdup(tmp_2->value);
		tmp_2 = tmp_2->next;
		counter++;
	}
	before_sep[counter] = NULL;
	return (before_sep);
}

char	**after_sep_func(t_hash *cmd)
{
	t_hash	*tmp;
	t_hash	*tmp_2;
	int		i;
	char	**after_arg;

	i = 0;
	tmp = cmd;
	while (!(tmp->key > 2 && tmp->key < 7) && tmp)
		tmp = tmp->next;
	if (tmp)
		tmp = tmp->next;
	tmp_2 = tmp;
	i = ft_strlen_before_sep(tmp);
	after_arg = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp_2 && !(tmp_2->key > 2 && tmp_2->key < 8))
	{
		after_arg[i++] = ft_strdup(tmp_2->value);
		tmp_2 = tmp_2->next;
	}
	after_arg[i] = NULL;
	return (after_arg);
}

void	next_step(t_hash **cmd)
{
	while (*cmd && !((*cmd)->key > 2 && (*cmd)->key < 7))
		*cmd = (*cmd)->next;
	if (*cmd)
		*cmd = (*cmd)->next;
}

void	execute_in_redir(t_main *main, char **env, t_bt *bts)
{
	if (!main->no_exec)
		execute(main->cur_md, main, env, bts);
	ft_close(main->out);
	dup2(main->fd_out, STDOUT);
	ft_close(main->in);
	dup2(main->fd_in, STDIN);
	free_split(main->cur_md);
}

void	redir(t_main *main, char **env, t_bt *bts)
{
	t_hash	*tmp;
	int		prev;

	tmp = main->current_cmd;
	prev = 0;
	main->cur_md = before_sep_func(tmp);
	init_new_value(main);
	while (tmp)
	{
		if (cur_sep(tmp) == INPUT)
			make_input(main, tmp);
		if (cur_sep(tmp) == TRUNC)
			make_output(main, tmp);
		if (cur_sep(tmp) == APPEND)
			make_append(main, tmp);
		if (cur_sep(tmp) == HER)
			make_heredoc(main, tmp);
		prev = cur_sep(tmp);
		next_step(&tmp);
	}
	execute_in_redir(main, env, bts);
}
