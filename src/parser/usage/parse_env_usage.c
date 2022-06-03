/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_usage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:37:37 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/03 20:38:11 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int		env_arg_len(char *str, int i)
{
	int	start;
	int	end;

	i++;
	start = i;
	while (str[i] && !is_spec_symbol(str[i]))
		i++;
	end = i;
	return (end - start);
}

void	str_delete_symbol(t_hash *hash, int i)
{
	while (hash->value[i])
	{
		hash->value[i] = hash->value[i + 1];
		i++;
	}
}
