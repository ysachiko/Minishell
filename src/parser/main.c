/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:25:20 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/09 15:45:08 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "string.h"

//SIGNALS
void	handler(int sig)
{
	//exit_status += sig;
	if (sig == SIGINT)
	{
		//exit_status = 130;
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("",0);
		rl_redisplay();
	}
}

void	handler2(int sig)
{
	//exit_status += sig;
	if (sig == SIGINT)
	{
		//exit_status = 130;
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("",0);
		rl_redisplay();
	}
}

void	free_hash(t_main *main)
{
	t_hash	*head;
	t_hash	*tmp;

	head = main->hash_head;
	while (head)
	{
		if (head->value)
			free (head->value);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	free_env(t_main *main)
{
	t_env	*head;
	t_env	*tmp;

	head = main->env_list;
	while (head)
	{
		free(head->value);
		free(head->key);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_main	*main;

	(void )argc;
	(void )argv;
	main = malloc(sizeof(t_main));
	init_env(main, env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handler);
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		if (!main->line)
		{
			free(main->line);
			free_env(main);
			free (main);
			exit(EXIT_FAILURE);
		}
		add_history(main->line);
		parser(main);
		free(main->line);
		free_hash(main);
	}
	free_env(main);
	free (main);
}
