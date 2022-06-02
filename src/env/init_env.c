/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:11:21 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/02 19:50:06 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	init_env(t_main *main, char **env)
{
	t_env	*new;
	t_env	*env_head;
	int		i;

	i = 0;
	env_head = malloc(sizeof(t_env));
	env_head->next = NULL;
	env_head->arg = ft_strdup(env[0]);
	i++;
	main->env_list = env_head;
	while (env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env));
		new->arg = ft_strdup(env[i]);
		new->next = NULL;
		env_head->next = new;
		env_head = new;
		i++;
	}
	return (0);
}

char	*find_path(t_env *head)
{
	t_env	*tmp;
	char	*path_line;
	int		i;

	tmp = head;
	i = 5;
	path_line = NULL;
	while (tmp)
	{
		if (tmp->arg[0] == 'P' && tmp->arg[1] == 'A' && tmp->arg[2] == 'T' \
			&& tmp->arg[3] == 'H' && tmp->arg[4] == '=')
			break;
		tmp = tmp->next;
	}
	path_line = malloc(sizeof(char) * (ft_strlen(tmp->arg) - 3));
	while (tmp->arg[i])
	{
		path_line[i - 5] = tmp->arg[i];
		i++;
	}
	return (path_line);
}
