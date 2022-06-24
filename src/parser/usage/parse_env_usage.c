/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_usage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:37:37 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/24 17:17:04 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	env_arg_len(char *str, int i)
{
	int	start;
	int	end;

	i++;
	start = i;
	while (str[i] && !is_spec_symbol(str[i]))
	{
		i++;
		if (str[i - 1] == '?')
			break ;
	}
	end = i;
	return (end - start);
}

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
		if (str[j] == '?')
			break ;
	}
	arg[k] = '\0';
	return (arg);
}

void	set_empty_arg(t_hash *hash, int i, char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		str_delete_symbol(hash, i);
		j++;
	}
	str_delete_symbol(hash, i);
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
	after_arg[counter] = '\0';
	return (after_arg);
}

char	*get_str_before_arg(t_hash *hash, int i)
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
