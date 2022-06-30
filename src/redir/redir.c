/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:34:04 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/30 16:48:49 by ysachiko         ###   ########.fr       */
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

void	clean_seps(char	**after_sep, char **before_sep)
{
	free_split(after_sep);
	free_split(before_sep);
	return ;
}

void	redir(t_main *main, char **env, t_bt *bts)
{
	t_hash	*tmp;
	t_hash	*tmp_2;

	tmp = main->current_cmd;
	tmp_2 = main->current_cmd;
	main->no_exec = 0;
	main->cur_md = before_sep_func(tmp_2);
	while (tmp)
	{
		if (cur_sep(tmp) == INPUT)
			make_input(main, env, bts, tmp);
		if (cur_sep(tmp) == TRUNC)
			make_output(main, env, bts, tmp);
		if (cur_sep(tmp) == APPEND)
			make_append(main, env, bts, tmp);
		if (cur_sep(tmp) == HER)
			make_heredoc(main, env, bts, tmp);
		next_step(&tmp);
	}
}
