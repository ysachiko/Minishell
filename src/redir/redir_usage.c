/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:46:21 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 16:47:43 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	ft_str_arr_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

int	ft_strlen_before_sep(t_hash *cmd)
{
	int		i;
	t_hash	*tmp;

	tmp = cmd;
	i = 0;
	if (tmp)
	{
		while (tmp && !(tmp->key > 2 && tmp->key < 7))
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}

int	is_redir(t_main *main)
{
	t_hash	*tmp;

	tmp = main->current_cmd;
	while (tmp)
	{
		if (tmp->key > 2 && tmp->key < 6)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	cur_sep(t_hash *hash)
{
	t_hash	*tmp;

	tmp = hash;
	while (tmp && !(tmp->key > 2 && tmp->key < 7))
		tmp = tmp->next;
	if (tmp)
		return (tmp->key);
	else
		return (-1);
}
