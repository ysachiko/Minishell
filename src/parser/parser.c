/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:08 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/01 19:27:20 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_space(char c)
{
	if (c == ' ' || c == '	' || c == '\t' || c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int is_single_quote(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	is_double_quote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

char	*str_realloc(char *str)
{
	char	*new_str;
	int		len;

	if (!str)
	{
		new_str = malloc(sizeof(char) * 2);
		new_str[0] ='\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * len + 2);
	ft_strlcpy(new_str, str, len + 1);
	return (new_str);
}

void	str_add_new_symbol(char *str, char symbol)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = symbol;
	str[i + 1] = '\0';
}

void make_head_token(t_main *main, t_hash **head)
{
	int		counter;
	char	*buf;

	counter = 0;
	buf = NULL;
	while (main->line[counter] != '\0')
	{
		if (!(is_space(main->line[counter]) || is_double_quote(main->line[counter]) || is_single_quote(main->line[counter])))
		{
			buf = str_realloc(buf);
			str_add_new_symbol(buf, main->line[counter]);
		}
		else if ((is_space(main->line[counter]) || is_double_quote(main->line[counter]) || is_single_quote(main->line[counter]) || main->line[counter] == '\0'))
		{
			*head = ft_lstnew_head(buf, buf);

			printf("%s", buf);
			return ;
		}
		counter++;
	}

}

void	parser(t_main *main)
{
	t_hash	*head;
	char	*line;

	main->current_symbol = 0;
	make_head_token(main, &head);
	printf("%s, %s", head->key, head->value);
}
