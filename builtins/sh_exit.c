/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:57:31 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/29 19:44:57 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	sh_exit(char **args, t_main *main)
{
	if (args[1] && args[2])
	{
		g_exit_status = 1;
		printf("bash: exit: too many arguments\n");
	}
	else if (args[1] && ft_strisnum(args[1]) == 0)
	{
		g_exit_status = 255;
		ft_putstr_fd("bash: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		main->exit_flag = 0;
	}
	else if (args[1])
	{
		main->exit_flag = 0;
		g_exit_status = ft_atoi(args[1]);
	}
	else
	{
		g_exit_status = 0;
		main->exit_flag = 0;
	}
	return (g_exit_status);
}
