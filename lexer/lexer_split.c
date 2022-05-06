/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:25:29 by ysachiko          #+#    #+#             */
/*   Updated: 2022/05/06 18:56:54 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "string.h"

static int	unleah(char **str, int size)
{
	while (size--)
		free(str[size]);
	return (-1);
}

int	check_word(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\r')
		return (1);
	else if (c == '\n')
		return (1);
	else if (c == '\v')
		return (1);
	else if (c == '\f' )
		return (1);
	return (0);
}

int	skip_and_count(int *i, const char *str, char sign, int *words)
{
	(*i)++;
	while (str[*i] != sign && str[*i] != '\0')
		(*i)++;
	(*words)++;
	if (str[*i] == '\0')
		return (1);
	(*i)++;
	while (!check_word(str[*i]) && str[*i] != '\0')
		(*i)++;
	return (0);
}

static int	count_words(const char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (skip_and_count(&i, str, '"', &words))
				break ;
		}
		if (str[i] == 39)
		{
			if (skip_and_count(&i, str, 39, &words))
				break ;
		}
		if ((check_word(str[i + 1]) || str[i + 1] == '\0') == 1
			&& (check_word(str[i]) || str[i] == '\0') == 0)
			words++;
		if (str[i] != '\0')
			i++;
	}
	return (words);
}

static void	write_word(char *dest, const char *from, int j)
{
	int	i;

	i = 0;
	while (i < j && from[i] != '\0')
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static int	write_split(char **split, const char *str)
{
	int	i;
	int	j;
	int	word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while ((check_word(str[i]) && str[i] != '\0'))
			i++;
		// printf("%c", str[i]);
		if (str[i] != '\0')
		{
			j = 0;
			if (str[i] == '"')
			{
				i++;
				while (str[i + j] != '"' && str[i + j] != '\0')
					j++;
				while (!check_word(str[i + j]) && str[i + j] != '\0')
					j++;
				split[word] = (char *)malloc(sizeof(char) * (j + 1));
				write_word(split[word], str + (i-1), j + 1);
				i += j;
				word++;
			}
			else if (str[i] == 39)
			{
				i++;
				while (str[i + j] != 39 && str[i + j] != '\0')
					j++;
				while (!check_word(str[i + j]) && str[i + j] != '\0')
					j++;
				split[word] = (char *)malloc(sizeof(char) * (j + 1));
				write_word(split[word], str + (i -1), j + 1);
				i += j;
				word++;
			}
			else if (str[i] != '"' && str[i] != 39 && !check_word(str[i]))
			{
				while (!check_word(str[i + j]) && str[i + j] != '\0')
					j++;
				split[word] = (char *)malloc(sizeof(char) * (j + 1));
				write_word(split[word], str + (i), j);
				i += j;
				word++;
			}
			i++;
		}
	}
	return (0);
}

char	**split_args(char *line)
{
	int		words;
	char	**res;

	words = count_words(line);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (res == NULL)
		return (NULL);
	res[words] = 0;
	write_split(res, line);
	return (res);
}

// int main(void)
// {
// 	char **line =  split_args("a b c d e");
// }
