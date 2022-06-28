/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:48:46 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/28 18:56:05 by ysachiko         ###   ########.fr       */
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

int	m_str_refactor(t_main *main, char **str, int i)
{
	char	*arg;
	char	*before_arg;
	char	*after_arg;
	char	*tmp;
	int		len;

	before_arg = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(before_arg, *str, i + 1);
	arg = get_arg_sep(*str, i);
	tmp = ft_strjoin(before_arg, " ");
	free(before_arg);
	before_arg = ft_strjoin(tmp, arg);
	len = ft_strlen(arg);
	after_arg = sep_after_arg(*str, i + ft_strlen(arg));
	free(arg);
	arg = ft_strjoin(before_arg, " ");
	free(tmp);
	tmp = ft_strjoin(arg, after_arg);
	free(*str);
	*str = ft_strdup(tmp);
	free(tmp);
	free(arg);
	free(after_arg);
	free(before_arg);
	return (i + len);
}

void	divide_str(char **str, t_main *main)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' && !main->in_single_quots)
		{
			if (main->in_double_quots)
				main->in_double_quots = 0;
			else
				main->in_double_quots = 1;
		}
		if ((*str)[i] == '\'' && !main->in_double_quots)
		{
			if (main->in_single_quots)
				main->in_single_quots = 0;
			else
				main->in_single_quots = 1;
		}
		if (is_t((*str)[i]) && (!main->in_single_quots && !main->in_double_quots))
		{
			i = m_str_refactor(main, str, i);
		}
		i++;
	}
}

void	make_lexer(t_main	*main)
{
	t_hash	*head;
	char	*tmp;

	main->current_symbol = 0;
	main->free_quote_flag = 1;
	head = NULL;
	tmp = ft_strdup(main->line);
	free(main->line);
	main->in_double_quots = 0;
	main->in_single_quots = 0;
	divide_str(&tmp, main);
	main->line = ft_strdup(tmp);
	free(tmp);
	lexer(main, &head);
	parse_lexer_list(head);
	main->hash_head = head;
	main->tmp2 = head;
}

void	add_new_value(t_hash **head, t_hash **tmp)
{
	ft_lstadd_back_hash(head, ft_lstnew_hash((*tmp)->key, \
		ft_strdup((*tmp)->value)));
	*tmp = (*tmp)->next;
}

t_hash	*make_current_cmd(t_main *main)
{
	t_hash	*head;
	t_hash	*tmp;

	tmp = main->tmp2;
	if (tmp)
	{
		head = ft_lstnew_hash(tmp->key, ft_strdup(tmp->value));
		tmp = tmp->next;
		while (tmp && tmp->prev->key != PIPE)
		{
			add_new_value(&head, &tmp);
			if (tmp && tmp->prev->key != PIPE)
			{
				if (tmp->key == PIPE)
				{
					add_new_value(&head, &tmp);
					break ;
				}
			}
		}
	}
	if (!tmp)
		main->end_flag = 0;
	main->tmp2 = tmp;
	return (head);
}

int	parse_env(t_main *main, t_hash *head)
{
	t_hash	*hash;
	int		i;

	hash = head;
	i = 0;
	while (hash)
	{
		main->in_double_quots = 0;
		main->in_single_quots = 0;
		env_str_refactor(main, hash);
		hash = hash->next;
	}
	return (0);
}
