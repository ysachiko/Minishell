/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:35:45 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/04 15:53:48 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

char	*find_env(char *str, int i)
{
	int		arg_length;
	char	*arg;
	int		j;
	int		k;

	arg_length = env_arg_len(str, i);
	arg = malloc(sizeof(char) * arg_length + 1);
	j = i + 1;
	k = 0;
	while (str[j] && !is_spec_symbol(str[j]) && !is_space(str[j]))
	{
		arg[k] = str[j];
		k++;
		j++;
	}
	arg[k] = '\0';
	return (arg);
}

void	set_empty_arg(t_hash *hash, int	i, char	*arg)
{
	int	j = 0;

	while (arg[j])
	{
		str_delete_symbol(hash, i);
		j++;
	}
	str_delete_symbol(hash, i);
	printf("\n");
}

char	*get_str_after_arg(t_hash *hash, int i, char *arg)
{
	char	*after_arg;
	int		counter;
	int		len;

	counter = i;
	len = 0;
	while (hash->value[counter])
	{
		counter++;
		len++;
	}
	after_arg = malloc(sizeof(char) * len - ft_strlen(arg) + 1);
	counter = 0;
	while (hash->value[i + ft_strlen(arg) + 1])
	{
		after_arg[counter] = hash->value[i + ft_strlen(arg) + 1];
		i++;
		counter++;
	}
	return (after_arg);
}

char	*get_str_before_arg(t_hash *hash, int i, char *arg)
{
	char	*before_arg;
	int		count;

	count = 0;
	while (hash->value[count] && count < i)
		count++;
	before_arg = malloc(sizeof(char) * (count + 1));
	count = 0;
	while (hash->value[count] && count < i)
	{
		before_arg[count] = hash->value[count];
		count++;
	}
	before_arg[count] = '\0';
	return (before_arg);
}

int	extend_str_arg(t_hash *hash, int i, char *arg, t_env *node)
{
	char	*after_arg;
	char	*before_arg;
	char	*new_str;

	after_arg = get_str_after_arg(hash, i, arg);
	before_arg = get_str_before_arg(hash, i, arg);
	new_str = ft_strjoin(ft_strjoin(before_arg, node->value), after_arg);
	free(hash->value);
	hash->value = new_str;
	free(after_arg);
	free(before_arg);
	return (ft_strlen(node->value));
}

int	arg_str_refactor(t_main *main, t_hash *hash, int i)
{
	t_env	*node;
	char	*arg;

	arg = find_env(hash->value, i);
	node = find_key_node(arg, main->env_list);
	if(!node)
	{
		set_empty_arg(hash, i, arg);
		return (i);
	}
	else
		return (extend_str_arg(hash, i, arg, node));
	free(arg);
}

int		str_refactor(t_main *main, t_hash *hash, int i)
{
	int	arg_length;

	arg_length = env_arg_len(hash->value, i);
	if (arg_length == 0)
		str_delete_symbol(hash, i);
	if (arg_length)
			i += arg_str_refactor(main, hash, i);
	return (i);
}

void	env_str_refactor(t_main *main,t_hash *hash)
{
	int	i;

	i = 0;
	while (hash->value[i])
	{
		if (hash->value[i] == '"' && !main->in_single_quots)
		{
			if (main->in_double_quots)
				main->in_double_quots = 0;
			else
				main->in_double_quots = 1;
		}
		if (hash->value[i] == '\'' && !main->in_double_quots)
		{
			if (main->in_single_quots)
				main->in_single_quots = 0;
			else
				main->in_single_quots = 1;
		}
		if (hash->value[i] == '$' && !main->in_single_quots)
		{
			i = str_refactor(main, hash, i);
		}
		i++;
	}
}

int	parse_env(t_main *main, t_hash *head)
{
	t_hash	*hash;

	int		i;

	hash = head;
	i = 0;
	while (hash)
	{
		main->in_double_quots = 0;
		main->in_single_quots = 0;
		env_str_refactor(main, hash);
		hash = hash->next;
	}
	return (0);
}
