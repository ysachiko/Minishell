/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:28:53 by kezekiel          #+#    #+#             */
/*   Updated: 2022/07/01 15:34:13 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	**path_parser(t_env *all)
{
	char	**paths;
	char	*val;
	t_env	*tmp;

	tmp = search_env(all, "PATH");
	if (tmp)
	{	
		val = tmp->value;
		paths = ft_split(val, ':');
		return (paths);
	}
	return (NULL);
}

char	*env_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path_cmd;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			end_prog(ERROR_EXEC_BIN_INIT, 1, 0);
		path_cmd = ft_strjoin(tmp, cmd);
		if (!path_cmd)
		{
			free (tmp);
			end_prog(ERROR_EXEC_BIN_INIT, 1, 0);
		}
		free (tmp);
		if (!access(path_cmd, X_OK))
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

char	*search_paths(char **paths, char *cmd)
{
	char	*path;

	if (*cmd && (!ft_strncmp(cmd, "./", 2) || cmd[0] == '/'))
	{
		if (!access(cmd, X_OK))
		{
			path = ft_strdup(cmd);
			if (!path)
				end_prog(ERROR_EXEC_BIN_INIT, 1, 0);
			return (path);
		}
	}
	path = env_path(paths, cmd);
	return (path);
}
