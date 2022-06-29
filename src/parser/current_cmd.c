/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:48:46 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/29 16:51:34 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

void	make_lexer(t_main	*main)
{
	t_hash	*head;
	char	*tmp;

	main->current_symbol = 0;
	main->free_quote_flag = 1;
	head = NULL;
	tmp = ft_strdup(main->line);
	free(main->line);
	main->dbl_qts = 0;
	main->sngl_qts = 0;
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
				if (tmp->key > ARG)
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
		main->dbl_qts = 0;
		main->sngl_qts = 0;
		env_str_refactor(main, hash);
		hash = hash->next;
	}
	return (0);
}
