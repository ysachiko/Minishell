/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:14:21 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/26 23:26:55 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"


int	g_exit_status;

//SIGNALS
void handler(int sig)
{
	//exit_status += sig;
	if (sig == SIGINT)
	{
		//exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}

void handler2(int sig)
{
	//exit_status += sig;
	if (sig == SIGINT)
	{
		//exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
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

void	redir(t_main *main, char **env)
{
	int		fd[2];
	int		pid;
	char	**args;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT);
		close(fd[0]);
		args = hash_parser(main->current_cmd);
		execute(args, main, env);
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

int	execute_cycle(t_main *main, char **env)
{
	char	**args;

	main->end_flag = 1;
	while(main->end_flag)
	{
		parser(main);
		if (current_sep(main))
			redir(main, env);
		else if (!current_sep(main) && main->prev_sep)
		{
			args = hash_parser(main->current_cmd);
			execute(args, main, env);
			dup2(main->fd_out, STDOUT);
			// dup2(main->fd_in, STDIN);
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

int main(int ac, char **av, char **env)
{
	char *line;
	char **args;
	t_main	*main;

	g_exit_status = 0;
	main = malloc(sizeof(t_main));
	main->fd_in = dup(STDIN);
	main->fd_out = dup(STDOUT);
	init_env(main, env);
	signal(SIGQUIT, SIG_IGN);
	main->exit_flag = 1;
	while(main->exit_flag)
	{
		signal(SIGINT, handler);
		display_ctrl_c(1);
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		if (main->line && !check_input(main->line))
		{
			free(main->line);
			continue;
		}
		signal(SIGINT, SIG_IGN);
		if (!main->line)
			exit(EXIT_FAILURE);
		add_history(main->line);
		display_ctrl_c(0);
		make_lexer(main);
		execute_cycle(main, env);
		/*printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();*/
		// debug_print_list(main->hash_head);
		free_hash(main->hash_head);
		free(main->line);
	}
	clean_env(main->env_list);
	//clean_up();
	return(g_exit_status);
}
