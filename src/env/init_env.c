/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:11:21 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/24 17:22:43 by ysachiko         ###   ########.fr       */
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
	env_head->key = take_env_key(env[0]);
	env_head->value = take_env_value(env[0]);
	i++;
	main->env_list = env_head;
	while (env && env[0] && env[i])
	{
		new = malloc(sizeof(t_env));
		new->key = take_env_key(env[i]);
		new->value = take_env_value(env[i]);
		new->next = NULL;
		env_head->next = new;
		env_head = new;
		i++;
	}
	return (0);
}

t_env	*find_key_node(char *str, t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp && ft_strcmp(tmp->key, str))
		tmp = tmp->next;
	return (tmp);
}

char	*take_env_key(char *str)
{
	int		i;
	char	*key;

	key = NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(key, str, i + 1);
	return (key);
}

char	*take_env_value(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	size = ft_strlen(str) - i;
	value = malloc(sizeof(char) * size + 1);
	while (str[i])
	{
		value[j] = str[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}
