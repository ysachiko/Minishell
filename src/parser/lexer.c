/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:25:20 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/02 19:52:13 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "string.h"

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	**args;
	t_main	*main;
	//int status;


	//signal(SIGINT, handler);
	//signal(SIGQUIT, SIG_IGN);
	main = malloc(sizeof(t_main));
	init_env(main, env);
	printf("\n\n*****ENV_TEST*******\n\n");
	DEBUG_PRINT_LIST_2(main->env_list);
	printf("\n\n*****ENV_TEST*******\n\n");
	printf("%s", find_path(main->env_list));
	printf("\n*****ENV_PATH_TEST*******\n");
	while(1)
	{
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		add_history(main->line);
		parser(main);
		if (!main->line)
			exit(EXIT_FAILURE);
		// rl_redisplay();
	}
	// free(line);
	// free(args);
}
