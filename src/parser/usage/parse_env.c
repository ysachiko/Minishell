/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:35:45 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/03 20:40:24 by ysachiko         ###   ########.fr       */
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

void	arg_str_refactor(t_main *main, t_hash *hash, int i)
{
	t_env	*node;

	node = find_key_node(find_env(hash->value, i), main->env_list);
	if(!node)
		printf("PIZDA");
	else
		printf("%s", node->value);
}

int		str_refactor(t_main *main, t_hash *hash, int i)
{
	int	arg_length;

	arg_length = env_arg_len(hash->value, i);
	if (arg_length == 0)
		str_delete_symbol(hash, i);
	if (arg_length)
		{
			arg_str_refactor(main, hash, i);
			i += arg_length;
		}
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
			main->in_double_quots = 1;
		}
		if (hash->value[i] == '\'' && !main->in_double_quots)
		{
			if (main->in_single_quots)
				main->in_single_quots = 0;
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
