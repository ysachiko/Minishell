/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:34:04 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/28 18:52:59 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

void	input(t_main *mini)
{
	char	**args;

	args = hash_parser(mini->current_cmd);
	close(mini->fd_in);
	mini->fd_in = open(args[1], O_RDONLY, S_IRWXU);
	if (mini->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		// mini->ret = 1;
		mini->no_exec = 1;
		free(args);
		return ;
	}
	free(args);
	dup2(mini->fd_in, STDIN);
}

// void	redir(t_main *main)
// {

// }
