/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:08 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/04 15:56:31 by ysachiko         ###   ########.fr       */
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
	main->current_symbol = extend_string(&argument, 39, counter);
	return (argument);
}

char	*take_double_quote_args(t_main *main, int counter)
{
	char	*argument;

	argument = NULL;
	if (is_double_quote(main->line[counter + 1]) || \
		main->line[counter + 1] == '\0')
	{
		if (main->line[counter])
			main->current_symbol = counter + 2;
		else
			main->current_symbol = counter + 1;
		main->free_quote_flag = 0;
		return ("\"\"");
	}
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
	main->current_symbol = extend_string(&argument, '"', counter);
	return (argument);
}

char	*take_simple_argument(t_main *main, int counter)
{
	char	*argument;
	char	*tmp;

	argument = malloc(sizeof(char) * 1);
	argument[0] = '\0';
	while (main->line[counter] && !is_space(main->line[counter]))
	{
		if (is_double_quote(main->line[counter]))
		{
			tmp = take_double_quote_args(main, counter);
			argument = ft_strjoin(argument, tmp);
			if (main->free_quote_flag)
				free (tmp);
			counter = main->current_symbol;
		}
		if (is_single_quote(main->line[counter]))
		{
			tmp = take_single_quote_arg(main, counter);
			argument = ft_strjoin(argument, tmp);
			if (main->free_quote_flag)
				free (tmp);
			counter = main->current_symbol;
		}
		if (!is_space(main->line[counter]) && main->line[counter])
		{
			argument = str_realloc(argument);
			str_add_new_symbol(argument, main->line[counter]);
			counter++;
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

// void	str_empty_refactor(t_main *main,t_hash *hash)
// {
// 		int	i;

// 	i = 0;
// 	while (hash->value[i])
// 	{
// 		if (hash->value[i] == '"' && !main->in_single_quots)
// 		{
// 			if (main->in_double_quots)
// 				main->in_double_quots = 0;
// 			else
// 				main->in_double_quots = 1;
// 		}
// 		if (hash->value[i] == '\'' && !main->in_double_quots)
// 		{
// 			if (main->in_single_quots)
// 				main->in_single_quots = 0;
// 			else
// 				main->in_single_quots = 1;
// 		}
// 		if (hash->value[i] == '"' && !main->in_single_quots)
// 		{

// 		}
// 		i++;
// 	}
// }

// ВЫШЕ УДАЛЕНИЕ ТИПА e''c''h''o'' = echo ДОделаю позже ЧИТАЮЩЕМУ РЕСПЕКТ, КРУТАНИ ЗА МЕНЯ ВЕРТУХУ

void	delete_empty(t_main *main, t_hash *head)
{
	t_hash	*node;

	node = head;
	while (node)
	{
		main->in_double_quots = 0;
		main->in_single_quots = 0;
		// str_empty_refactor(main, node);
		node = node->next;
	}
}

void	parser(t_main *main)
{
	t_hash	*head;
	char	*line;

	main->current_symbol = 0;
	main->free_quote_flag = 1;
	lexer(main, &head);
	delete_empty(main, head);
	parse_env(main, head);
	parse_lexer_list(main, head);
	DEBUG_PRINT_LIST(head);
}
