/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:14:21 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 16:58:02 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

int	g_exit_status;

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

void	minipipe(t_main *main, char **env, t_bt *bts)
{
	int		fd[2];
	int		pid;
	char	**args;
	char	**path;
	char	*cmd;

	args = hash_parser(main->current_cmd);
	path = path_parser(main->env_list);
	cmd = search_paths(path, args[0]);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT);
		close(fd[0]);
		if (execve(cmd, args, env) == -1)
			perror("exec failure");
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

int	execute_cycle(t_main *main, char **env, t_bt *bts)
{
	char	**args;

	main->end_flag = 1;
	while (main->end_flag)
	{
		parser(main);
		if (current_sep(main) == PIPE)
			minipipe(main, env, bts);
		else if (is_redir(main))
			redir(main, env, bts);
		else if (!current_sep(main) && main->prev_sep)
		{
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
			free(args);
		}
		else
		{
			args = hash_parser(main->current_cmd);
			execute(args, main, env, bts);
			free(args);
		}
		main->prev_sep = current_sep(main);
		free_hash(main->current_cmd);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	**args;
	t_main	*main;
	t_bt	*bts;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	main = malloc(sizeof(t_main));
	main->fd_in = dup(STDIN);
	main->fd_out = dup(STDOUT);
	bts = malloc(sizeof(t_bt));
	init_bts(bts);
	init_env(main, env);
	signal(SIGQUIT, SIG_IGN);
	main->exit_flag = 1;
	main->no_exec = 0;
	while (main->exit_flag)
	{
		signal(SIGINT, handler);
		display_ctrl_c(1);
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		if (main->line && !check_input(main->line))
		{
			free(main->line);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		if (!main->line)
			exit(EXIT_FAILURE);
		add_history(main->line);
		display_ctrl_c(0);
		make_lexer(main);
		execute_cycle(main, env, bts);
		free_hash(main->hash_head);
		free(main->line);
	}
	clean_env(main->env_list);
	//clean_up();
	free(main);
	free(bts);
	return (g_exit_status);
}
