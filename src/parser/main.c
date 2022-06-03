/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:25:20 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/03 16:35:53 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "string.h"

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	**args;
	t_main	*main;
	t_env	*PATH;
	//int status;


	//signal(SIGINT, handler);
	//signal(SIGQUIT, SIG_IGN);
	main = malloc(sizeof(t_main));
	init_env(main, env);
	// PATH = find_key_node("PATHafa", main->env_list);
	// if (PATH)
	// 	printf("%s=%s", PATH->key, PATH->value);
	// printf("\n\n*****ENV_TEST*******\n\n");
	// DEBUG_PRINT_LIST_2(main->env_list);
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
