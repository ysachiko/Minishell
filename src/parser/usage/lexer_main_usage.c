/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_usage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:42:54 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 17:03:37 by ysachiko         ###   ########.fr       */
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

int	is_empty(char *str)
{
	if (!ft_strcmp(str, "\"\""))
		return (1);
	if (!ft_strcmp(str, "''"))
		return (1);
	if (str[0] == '\0')
		return (1);
	return (0);
}

void	quote_refactor(t_hash *hash)
{
	int	sngl_qts;
	int	dbl_qts;
	int	i;

	dbl_qts = 0;
	sngl_qts = 0;
	i = 0;
	if (!ft_strchr(hash->value, '\'') && !ft_strchr(hash->value, '"'))
		return ;
	while (hash->value[i])
	{
		if (is_double_quote(hash->value[i]))
		{
			dbl_qts = 1;
			str_delete_symbol(hash, i);
			while (is_double_quote(hash->value[i]))
				i++;
			str_delete_symbol(hash, i);
		}
		i++;
	}
}

int	parse_lexer_list(t_hash *head)
{
	t_hash	*hash;

	hash = head;
	while (hash)
	{
		if (is_empty(hash->value))
			hash->key = EMPTY;
		else if (!ft_strcmp(hash->value, "|"))
			hash->key = PIPE;
		else if (!ft_strcmp(hash->value, ">"))
			hash->key = TRUNC;
		else if (!ft_strcmp(hash->value, "<"))
			hash->key = INPUT;
		else if (!ft_strcmp(hash->value, ">>"))
			hash->key = APPEND;
		else if (!ft_strcmp(hash->value, "<<"))
			hash->key = HER;
		else if (hash->prev == NULL || hash->prev->key >= TRUNC)
			hash->key = CMD;
		else
			hash->key = ARG;
		hash = hash->next;
	}
	return (0);
}
