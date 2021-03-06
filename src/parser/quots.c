/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:56:55 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/24 16:18:07 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*take_single_quote_arg(t_main *main, int counter)
{
	char	*argument;

	argument = NULL;
	if (is_single_quote(main->line[counter + 1]) || \
		main->line[counter + 1] == '\0')
	{
		if (main->line[counter + 1])
			main->current_symbol = counter + 2;
		else
			main->current_symbol = counter + 1;
		main->free_quote_flag = 0;
		return ("''");
	}
	while (main->line[counter])
	{
		counter = extend_string(&argument, main->line[counter], counter);
		if (is_single_quote(main->line[counter]))
		{
			counter = extend_string(&argument, main->line[counter], counter);
			main->current_symbol = counter;
			return (argument);
		}
	}
	main->current_symbol = extend_string(&argument, 39, counter) - 1;
	return (argument);
}

char	*return_double_quotes(t_main *main, int counter)
{
	if (main->line[counter + 1])
		main->current_symbol = counter + 2;
	else
		main->current_symbol = counter + 1;
	main->free_quote_flag = 0;
	return ("\"\"");
}

char	*take_double_quote_args(t_main *main, int counter)
{
	char	*argument;

	argument = NULL;
	if (is_double_quote(main->line[counter + 1]) || \
		main->line[counter + 1] == '\0')
		return (return_double_quotes(main, counter));
	while (main->line[counter])
	{
		counter = extend_string(&argument, main->line[counter], counter);
		if (is_double_quote(main->line[counter]))
		{
			counter = extend_string(&argument, main->line[counter], counter);
			main->current_symbol = counter;
			return (argument);
		}
	}
	main->current_symbol = extend_string(&argument, '"', counter) - 1;
	return (argument);
}

void	refactor_double_quote_arg(t_main *main, int counter, char **argument)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = take_double_quote_args(main, counter);
	if (!ft_strcmp(tmp, "\"\""))
		return (ft_return_quots(tmp, argument, main));
	realloc_argument(argument, tmp);
	if (main->free_quote_flag)
		free (tmp);
}

void	refactor_single_quote_arg(t_main *main, int counter, char **argument)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = take_single_quote_arg(main, counter);
	if (!ft_strcmp(tmp, "''"))
		return (ft_return_quots(tmp, argument, main));
	realloc_argument(argument, tmp);
	if (main->free_quote_flag)
		free (tmp);
}
