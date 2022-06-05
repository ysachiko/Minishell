/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:25:20 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/05 19:55:24 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "string.h"

int	main(int argc, char **argv, char **env)
{
	t_main	*main;

	(void )argc;
	(void )argv;
	main = malloc(sizeof(t_main));
	init_env(main, env);
	while (1)
	{
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		add_history(main->line);
		parser(main);
		if (!main->line)
			exit(EXIT_FAILURE);
	}
	free (main);
}
