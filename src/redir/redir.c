/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:34:04 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/28 20:27:41 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	ft_strlen_before_sep(t_hash *cmd)
{
	int		i;
	t_hash	*tmp;

	tmp = cmd;
	i = 0;
	if (tmp)
	{
		while (!(tmp->key > 2 && tmp->key < 7))
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

// void	input(t_main *mini, char **args)
// {
// 	char	**args;

// 	close(mini->fd_in);
// 	mini->fd_in = open(args[1], O_RDONLY, S_IRWXU);
// 	if (mini->fd_in == -1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR);
// 		ft_putstr_fd(args[1], STDERR);
// 		ft_putendl_fd(": No such file or directory", STDERR);
// 		// mini->ret = 1;
// 		mini->no_exec = 1;
// 		free(args);
// 		return ;
// 	}
// 	free(args);
// 	dup2(mini->fd_in, STDIN);
// }

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
	while (!(tmp_2->key > 2 && tmp_2->key < 7) && tmp_2)
	{
		after_arg[i++] = ft_strdup(tmp_2->value);
		tmp_2 = tmp_2->next;
	}
	after_arg[i] = NULL;
	return(after_arg);
}

void	redir(t_main *main, char **env, t_bt *bts)
{
	t_hash	*tmp;
	char	**before_sep;
	char	**after_sep;

	tmp = main->current_cmd;
	debug_print_list(tmp);
	after_sep = after_sep_func(tmp);
	before_sep = before_sep_func(tmp);
	printf("\n%s %s\n", after_sep[0], after_sep[1]);
	while (!(tmp->key > 2 && tmp->key < 7) && tmp)
	{
		tmp = tmp->next;
	}
	// if (tmp->key == INPUT)
	// 	input(main, before_sep);
	// execute(cat, main, env, bts);
}
