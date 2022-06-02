/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_usage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:42:54 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/02 18:43:30 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

void	scip_space(t_main *main, int counter)
{
	while (main->line[counter] != '\0' && is_space(main->line[counter]))
		counter++;
	main->current_symbol = counter;
}

int	extend_string(char **argument, char symbol, int counter)
{
	*argument = str_realloc(*argument);
	str_add_new_symbol(*argument, symbol);
	return (counter + 1);
}
