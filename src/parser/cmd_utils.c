/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:03:11 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/29 20:50:58 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_t(char c)
{
	if (c == '|')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else
		return (0);
}

int	get_sep_len(char *str, int i)
{
	int	start;

	start = i;
	if (str[start] == '|')
		return (1);
	else if (str[start] == '>' && str[start + 1] == '>')
		return (2);
	else if (str[start] == '<' && str[start + 1] == '<')
		return (2);
	else if (str[start] == '>')
		return (1);
	else if (str[start] == '<')
		return (1);
	return (0);
}

char	*get_arg_sep(char *str, int i)
{
	int		arg_len;
	int		j;
	char	*arg;

	j = 0;
	arg_len = get_sep_len(str, i);
	arg = malloc(sizeof(char) * (arg_len + 1));
	while (j < arg_len)
	{
		arg[j] = str[i + j];
		j++;
	}
	arg[j] = '\0';
	return (arg);
}

char	*sep_after_arg(char *str, int i)
{
	char	*res;
	int		j;

	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	while (str[i])
	{
		res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	divide_str(char **str, t_main *main)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' && !main->sngl_qts)
		{
			if (main->dbl_qts)
				main->dbl_qts = 0;
			else
				main->dbl_qts = 1;
		}
		if ((*str)[i] == '\'' && !main->dbl_qts)
		{
			if (main->sngl_qts)
				main->sngl_qts = 0;
			else
				main->sngl_qts = 1;
		}
		if (is_t((*str)[i]) && (!main->sngl_qts && !main->dbl_qts))
		{
			i = m_str_refactor(str, i);
		}
		i++;
	}
}
