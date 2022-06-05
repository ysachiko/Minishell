/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_usage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:50:27 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/05 19:54:14 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	is_spec_symbol(char c)
{
	if (c == '"' || c == '/' || c == '\'' || c == '$' || \
		c == '.' || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	str_delete_symbol(t_hash *hash, int i)
{
	while (hash->value[i])
	{
		hash->value[i] = hash->value[i + 1];
		i++;
	}
}
