/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:14:08 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/30 16:50:19 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

int	current_sep(t_main *main)
{
	t_hash	*tmp;

	tmp = main->current_cmd;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->key == PIPE)
		return (PIPE);
	if (tmp->key == TRUNC)
		return (TRUNC);
	if (tmp->key == APPEND)
		return (APPEND);
	if (tmp->key == INPUT)
		return (INPUT);
	return (0);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

void	pipe_executor(t_main *main, char **env, t_bt *bts)
{
	char	**args;
	char	**path;
	char	*cmd;

	args = hash_parser(main->current_cmd);
	if (is_redir(main))
	{
		redir(main, env, bts);
		exit(g_exit_status);
	}
	else if (is_builtin(args[0]))
		child_builtin(main, env, bts, args);
	else
	{
		path = path_parser(main->env_list);
		cmd = search_paths(path, args[0]);
		if (execve(cmd, args, env) == -1)
			perror("exec failure");
	}
}

void	minipipe(t_main *main, char **env, t_bt *bts)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT);
		pipe_executor(main, env, bts);
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	else
	{
		wait(&pid);
		dup2(fd[0], STDIN);
		close(fd[1]);
		close(fd[0]);
		return ;
	}
}

void	last_pipe(t_main *main, char **env, t_bt *bts)
{
	char	**args;

	args = NULL;
	ft_close(STDOUT);
	dup2(main->fd_out, STDOUT);
	if (is_redir(main))
		redir(main, env, bts);
	else
	{
		args = hash_parser(main->current_cmd);
		execute(args, main, env, bts);
	}
	ft_close(STDIN);
	dup2(main->fd_in, STDIN);
	if (args)
		free(args);
}
