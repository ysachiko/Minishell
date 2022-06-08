/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_usage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:50:27 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/08 17:35:19 by ysachiko         ###   ########.fr       */
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

void	set_double_quote_flag_value(t_main *main)
{
	if (main->in_double_quots)
		main->in_double_quots = 0;
	else
		main->in_double_quots = 1;
}

void	set_single_quote_flag_value(t_main *main)
{
	if (main->in_single_quots)
		main->in_single_quots = 0;
	else
		main->in_single_quots = 1;
}

int	symbol_check(t_main *main, int counter)
{
	if (!is_space(main->line[counter]) && main->line[counter] && \
	!is_double_quote(main->line[counter]) \
		&& !is_single_quote(main->line[counter]))
		return (1);
	return (0);
}
