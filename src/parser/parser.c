/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:08 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/05 20:32:29 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	refactor_simple_arg(t_main *main, int counter, char **argument)
{
	char	*tmp;

	tmp = malloc(sizeof(char));
	tmp[0] = '\0';
	while (!is_space(main->line[counter]) && main->line[counter] && \
			!is_double_quote(main->line[counter]) \
				&& !is_single_quote(main->line[counter]))
	{
		tmp = str_realloc(tmp);
		str_add_new_symbol(tmp, main->line[counter]);
		counter++;
	}
	str_env_pars(main, &tmp);
	*argument = ft_strjoin(*argument, tmp);
	main->current_symbol = counter;
}

char	*take_simple_argument(t_main *main, int counter)
{
	char	*argument;

	argument = malloc(sizeof(char) * 1);
	argument[0] = '\0';
	while (main->line[counter] && !is_space(main->line[counter]))
	{
		main->free_quote_flag = 1;
		if (is_double_quote(main->line[counter]))
		{
			refactor_double_quote_arg(main, counter, &argument);
			counter = main->current_symbol;
		}
		if (is_single_quote(main->line[counter]))
		{
			refactor_single_quote_arg(main, counter, &argument);
			counter = main->current_symbol;
		}
		if (!is_space(main->line[counter]) && main->line[counter] && \
			!is_double_quote(main->line[counter]) \
				&& !is_single_quote(main->line[counter]))
		{
			refactor_simple_arg(main, counter, &argument);
			counter = main->current_symbol;
		}
	}
	main->current_symbol = counter;
	return (argument);
}

void	make_lexer_list(char *argument, t_hash **head)
{
	t_hash	*new;

	if (!*head)
	{
		*head = ft_lstnew_hash(-1, argument);
	}
	else
	{
		new = ft_lstnew_hash(-1, argument);
		ft_lstadd_back_hash(head, new);
	}
}

void	lexer(t_main *main, t_hash **head)
{
	int		counter;
	char	*buf;

	counter = 0;
	buf = NULL;
	while (main->line[counter] != '\0')
	{
		if (is_space(main->line[counter]))
		{
			scip_space(main, counter);
			counter = main->current_symbol;
		}
		if (main->line[counter] && !is_space(main->line[counter]))
		{
			buf = take_simple_argument(main, counter);
			make_lexer_list(buf, head);
			counter = main->current_symbol;
		}
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

void	parser(t_main *main)
{
	t_hash	*head;

	main->current_symbol = 0;
	main->free_quote_flag = 1;
	lexer(main, &head);
	parse_lexer_list(head);
	debug_print_list(head);
	main->hash_head = head;
}
