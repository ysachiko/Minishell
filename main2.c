/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:14:21 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/30 16:05:43 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

int	g_exit_status;

void	child_builtin(t_main *main, char **env, t_bt *bts, char **args)
{
	int	i;

	i = 0;
	(void) env;
	while (i < 7)
	{
		if (ft_strcmp(args[0], bts->builtins[i]) == 0)
		{
			g_exit_status = (bts->built[i])(args, main);
			exit(g_exit_status);
		}
		i++;
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
		else if (is_redir(main) && main->prev_sep != PIPE)
			redir(main, env, bts);
		else if (current_sep(main) != PIPE && main->prev_sep)
			last_pipe(main, env, bts);
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

void	init_main(t_main *main, char **env, t_bt *bts)
{
	g_exit_status = 0;
	main->exit_flag = 1;
	main->no_exec = 0;
	main->fd_in = dup(STDIN);
	main->fd_out = dup(STDOUT);
	init_bts(bts);
	init_env(main, env);
}

void	execute_main(t_main *main, char **env, t_bt *bts)
{
	add_history(main->line);
	display_ctrl_c(0);
	make_lexer(main);
	execute_cycle(main, env, bts);
	if (main->prev_sep == PIPE && !main->end_flag)
	{
		ft_close(STDOUT);
		dup2(main->fd_out, STDOUT);
		ft_close(STDIN);
		dup2(main->fd_in, STDIN);
		ft_putstr_fd("bash: ", STDERR);
		ft_putendl_fd("syntax error: unexpected end of file", STDERR);
		g_exit_status = 1;
	}
	free_hash(main->hash_head);
	free(main->line);
}

int	main(int ac, char **av, char **env)
{
	t_main	*main;
	t_bt	*bts;

	signal(SIGQUIT, SIG_IGN);
	werror_killer(ac, av);
	main = malloc(sizeof(t_main));
	bts = malloc(sizeof(t_bt));
	init_main(main, env, bts);
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
			exit(0);
		execute_main(main, env, bts);
	}
	clean_up(main, bts);
	return (g_exit_status);
}
