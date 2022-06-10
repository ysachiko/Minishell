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
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		if (!main->line)
			exit(EXIT_FAILURE);
		add_history(main->line);
		//args = ft_split(main->line, ' ');
		parser(main);
		args = hash_parser(main->hash_head);
		execute(args, main);
		/*printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();*/
		free(main->line);
		free(args);
	}
	clean_env(&(main->env_list));
	//clean_up();
}
