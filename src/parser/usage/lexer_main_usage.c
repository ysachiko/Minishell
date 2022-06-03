/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main_usage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:42:54 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/03 19:20:31 by ysachiko         ###   ########.fr       */
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

int		is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	return (0);
}

int		is_empty(char *str)
{
	if (!ft_strcmp(str, "\"\"") )
		return (1);
	if (!ft_strcmp(str, "''"))
		return (1);
	return (0);
}

int	parse_lexer_list(t_main *main, t_hash *head)
{
	t_hash	*hash;

	hash = head;
	while (hash)
	{
		if (is_builtin(hash->value))
			hash->key = CMD;
		if (is_empty(hash->value))
			hash->key = EMPTY;
		hash = hash->next;
	}
	return (0);
}

int	is_spec_symbol(char c)
{
	if (c == '"' || c == '/' || c == '\'' || c == '$' || \
		c == '.' || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}
