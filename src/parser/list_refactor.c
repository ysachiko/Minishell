/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_refactor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:21:57 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/24 14:57:12 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	refactor_simple_arg_2(t_main *main, int counter, char **argument)
{
	char	*tmp;
	char	*tmp_2;

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
	tmp_2 = ft_strjoin(*argument, tmp);
	free(*argument);
	*argument = ft_strdup(tmp_2);
	main->current_symbol = counter;
	free(tmp_2);
	free (tmp);
}

char	*take_simple_argument_2(t_main *main, int counter)
{
	char	*argument;

	argument = malloc(sizeof(char) * 1);
	argument[0] = '\0';
	while (main->line[counter] && !is_space(main->line[counter]))
	{
		main->free_quote_flag = 1;
		if (is_double_quote(main->line[counter]))
		{
			refactor_double_quote_arg_2(main, counter, &argument);
			counter = main->current_symbol;
		}
		if (is_single_quote(main->line[counter]))
		{
			refactor_single_quote_arg_2(main, counter, &argument);
			counter = main->current_symbol;
		}
		if (symbol_check(main, counter))
		{
			refactor_simple_arg_2(main, counter, &argument);
			counter = main->current_symbol;
		}
	}
	main->current_symbol = counter;
	return (argument);
}

void	refactor_list(t_hash *hash, t_main *main)
{
	t_hash	*head;
	char	*buf;

	head = hash;
	while (head)
	{
		free (main->line);
		main->line = ft_strdup(head->value);
		buf = (take_simple_argument_2(main, 0));
		free (head->value);
		head->value = ft_strdup(buf);
		free (buf);
		head = head->next;
	}
}

void	refactor_single_quote_arg_2(t_main *main, int counter, char **argument)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = take_single_quote_arg(main, counter);
	while (tmp[i])
	{
		tmp[i] = tmp[i + 1];
		i++;
	}
	tmp[ft_strlen(tmp) - 1] = '\0';
	realloc_argument(argument, tmp);
	if (main->free_quote_flag)
		free(tmp);
}

void	refactor_double_quote_arg_2(t_main *main, int counter, char **argument)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = take_double_quote_args(main, counter);
	while (tmp[i])
	{
		tmp[i] = tmp[i + 1];
		i++;
	}
	tmp[ft_strlen(tmp) - 1] = '\0';
	str_env_pars(main, &tmp);
	realloc_argument(argument, tmp);
	if (main->free_quote_flag)
		free (tmp);
}
