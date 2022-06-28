/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:37:23 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/28 18:18:05 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

static int	ft_wexitstatus(int x)
{
	return ((x >> 8) & 0x000000ff);
}

int	execute(char **args, t_main *all, char **env, t_bt *bts)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
		return (1);
	while (i < 7)
	{
		if (ft_strcmp(args[0], bts->builtins[i]) == 0)
			return (g_exit_status = (bts->built[i])(args, all));
		i++;
	}
	return (launch(args, all, env));
}

int	launch(char **args, t_main *all, char **env)
{
	pid_t	child;
	int		status;
	char	**path;
	char	*cmd;

	path = path_parser(all->env_list);
	cmd = search_paths(path, args[0]);
	child = fork();
	if (!child)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
		if (execve(cmd, args, env) == -1)
			perror("exec failure");
		exit(EXIT_FAILURE);
	}
	else if (child < 0)
		perror("error forking");
	else
		waitpid(child, &status, 0);
	g_exit_status = ft_wexitstatus(status);
	free_split(path);
	return (g_exit_status);
}
