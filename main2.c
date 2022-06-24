#include "includes/parser.h"

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

int	execute_cycle(t_main *main, char **env)
{
	char	**args;

	main->end_flag = 1;
	while(main->end_flag)
	{
		parser(main);
		args = hash_parser(main->current_cmd);
		execute(args, main, env);
		free(args);
		free_hash(main->current_cmd);
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	char *line;
	char **args;
	t_main	*main;

	main = malloc(sizeof(t_main));
	init_env(main, env);
	signal(SIGQUIT, SIG_IGN);
	while(1)
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
		display_ctrl_c(0);
		make_lexer(main);
		add_history(main->line);
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
}
