/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:54:41 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 18:10:29 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	args_size(char **args)
{
	int	i;

	i = 1;
	while (args[i])
		i++;
	return (i);
}

int	sh_echo(char **args, t_main *main)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	(void) main;
	if (args_size(args) > 1)
	{
		while (args[i] && !ft_strcmp(args[i], "-n"))
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], STDOUT);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putstr_fd(" ", STDOUT);
			i++;
		}
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}
