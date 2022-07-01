/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:48:09 by kezekiel          #+#    #+#             */
/*   Updated: 2022/07/01 15:29:23 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	lst_size(t_hash *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (i);
	while (lst)
	{
		if (lst->key == 1 || lst->key == 2)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	**hash_parser(t_hash *head)
{
	char	**args;
	t_hash	*tmp;
	int		i;

	args = malloc(sizeof(char *) * (lst_size(head) + 1));
	tmp = head;
	i = 0;
	while (tmp)
	{
		if (tmp->key == 1 || tmp->key == 2)
		{
			args[i] = tmp->value;
			i++;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

void	sort_swap(t_env *tmp, t_env *curr)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = curr->key;
	tmp_value = curr->value;
	curr->key = tmp->key;
	curr->value = tmp->value;
	tmp->key = tmp_key;
	tmp->value = tmp_value;
}

void	sort_env(t_env *copy)
{
	t_env	*curr;
	t_env	*tmp;

	curr = copy;
	if (!curr)
		return ;
	while (curr->next)
	{
		tmp = curr->next;
		while (tmp->next)
		{
			if (ft_strcmp(curr->key, tmp->key) > 0)
				sort_swap(tmp, curr);
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}
