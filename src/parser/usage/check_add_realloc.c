/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_add_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:54:16 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/02 16:57:03 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

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
		free(str);
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * len + 2);
	ft_strlcpy(new_str, str, len + 1);
	free (str);
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
