/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_usage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:50:27 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 16:52:56 by kezekiel         ###   ########.fr       */
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
	if (main->dbl_qts)
		main->dbl_qts = 0;
	else
		main->dbl_qts = 1;
}

void	set_single_quote_flag_value(t_main *main)
{
	if (main->sngl_qts)
		main->sngl_qts = 0;
	else
		main->sngl_qts = 1;
}

int	symbol_check(t_main *main, int counter)
{
	if (!is_space(main->line[counter]) && main->line[counter] && \
	!is_double_quote(main->line[counter]) \
		&& !is_single_quote(main->line[counter]))
		return (1);
	return (0);
}
