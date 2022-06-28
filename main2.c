/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:14:21 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/28 16:21:46 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

int	g_exit_status;

void	handler(int sig)
{
	g_exit_status += sig;
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler2(int sig)
{
	g_exit_status += sig;
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static int	check_input(char *input)
{
	while (*input)
	{
		if (*input == '|')
		{
			ft_putstr_fd("minishell: syntax error near \
unexpected token `|'\n", STDERR_FILENO);
			return (0);
		}
		if (*input == ' ' || *input == '\t')
			input++;
		else
			return (1);
	}
	return (0);
}

void	display_ctrl_c(int display)
{
	struct termios	t;

	tcgetattr(0, &t);
	if (display == 0)
		t.c_lflag |= ECHOCTL;
	else
		t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

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

void	minipipe(t_main *main, char **env)
{
	int		fd[2];
	int		pid;
	char	**args;
	char	**path;
	char	*cmd;

	args = hash_parser(main->current_cmd);
	path = path_parser(main->env_list);
	cmd = search_paths(path, args[0]);
	printf("\n%s\n", cmd);
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
		// mini->no_exec = 1;
		free(args);
		return ;
	}
	free(args);
	dup2(mini->fd_in, STDIN);
}

int	execute_cycle(t_main *main, char **env)
{
	char	**args;

	main->end_flag = 1;
	while(main->end_flag)
	{
		parser(main);
		if (current_sep(main) == PIPE)
			minipipe(main, env);
		else if (!current_sep(main) && main->prev_sep)
		{
			close(STDOUT);
			dup2(main->fd_out, STDOUT);
			args = hash_parser(main->current_cmd);
			execute(args, main, env);
			close(STDIN);
			dup2(main->fd_in, STDIN);
			free(args);
		}
		else
		{
			args = hash_parser(main->current_cmd);
			execute(args, main, env);
			free(args);
		}
		main->prev_sep = current_sep(main);
		free_hash(main->current_cmd);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	**args;
	t_main	*main;

	g_exit_status = 0;
	main = malloc(sizeof(t_main));
	main->fd_in = dup(STDIN);
	main->fd_out = dup(STDOUT);
	init_env(main, env);
	signal(SIGQUIT, SIG_IGN);
	main->exit_flag = 1;
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
		execute_cycle(main, env);
		free_hash(main->hash_head);
		free(main->line);
	}
	clean_env(main->env_list);
	//clean_up();
	return (g_exit_status);
}
