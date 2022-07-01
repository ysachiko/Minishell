/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:37:23 by ysachiko          #+#    #+#             */
/*   Updated: 2022/07/01 15:34:14 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

void	wait_child(pid_t child)
{
	waitpid(child, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
}

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		g_exit_status = UNKNOWN_COMMAND;
	else
		g_exit_status = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (g_exit_status);
}

int	launch(char **args, t_main *all, char **env)
{
	pid_t	child;
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
			error_message(args[0]);
		exit(g_exit_status);
	}
	else if (child < 0)
		perror("error forking");
	else
		wait_child(child);
	free_split(path);
	return (g_exit_status);
}
