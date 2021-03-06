/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:35:45 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 16:52:36 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	extend_str_arg(t_hash *hash, int i, char *arg, t_env *node)
{
	char	*after_arg;
	char	*before_arg;
	char	*new_str;
	char	*tmp;

	after_arg = get_str_after_arg(hash, i, arg);
	before_arg = get_str_before_arg(hash, i);
	tmp = ft_strjoin(before_arg, node->value);
	new_str = ft_strjoin(tmp, after_arg);
	free(hash->value);
	hash->value = ft_strdup(new_str);
	free(new_str);
	free(after_arg);
	free(before_arg);
	free(tmp);
	return (ft_strlen(node->value));
}

int	extend_exit_status(char *arg, t_hash *hash, int i)
{
	t_env	*tmp;
	int		res;

	tmp = malloc(sizeof(t_env));
	tmp->key = "?";
	tmp->value = ft_itoa(g_exit_status);
	tmp->next = NULL;
	res = extend_str_arg(hash, i, arg, tmp);
	free(tmp->value);
	free (tmp);
	return (res);
}

int	arg_str_refactor(t_main *main, t_hash *hash, int i)
{
	t_env	*node;
	char	*arg;
	int		pos;

	arg = find_env(hash->value, i);
	if (!ft_strcmp("?", arg))
	{
		pos = extend_exit_status(arg, hash, i);
		free(arg);
		return (pos);
	}
	node = find_key_node(arg, main->env_list);
	if (!node)
	{
		set_empty_arg(hash, i, arg);
		free(arg);
		return (i);
	}
	else
	{
		pos = extend_str_arg(hash, i, arg, node);
		free(arg);
		return (pos);
	}
}

int	str_refactor(t_main *main, t_hash *hash, int i)
{
	int	arg_length;

	arg_length = env_arg_len(hash->value, i);
	if (arg_length == 0)
		i ++;
	if (arg_length)
		i += arg_str_refactor(main, hash, i);
	return (i);
}

void	env_str_refactor(t_main *main, t_hash *hash)
{
	int	i;

	i = 0;
	while (hash->value[i])
	{
		if (hash->value[i] == '"' && !main->sngl_qts)
		{
			if (main->dbl_qts)
				main->dbl_qts = 0;
			else
				main->dbl_qts = 1;
		}
		if (hash->value[i] == '\'' && !main->dbl_qts)
		{
			if (main->sngl_qts)
				main->sngl_qts = 0;
			else
				main->sngl_qts = 1;
		}
		if (hash->value[i] == '$' && !main->sngl_qts)
		{
			i = str_refactor(main, hash, i);
		}
		i++;
	}
}
