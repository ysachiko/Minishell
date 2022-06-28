/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:48:09 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/28 17:53:17 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

t_env	*search_env(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_export(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (name && ft_isdigit(name[0]))
		return (0);
	i = 0;
	while (name && name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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

void	sort_env(t_env *copy)
{
	t_env	*curr;
	t_env	*tmp;
	char	*tmp_key;
	char	*tmp_value;

	curr = copy;
	if (!curr)
		return ;
	while (curr->next)
	{
		tmp = curr->next;
		while (tmp->next)
		{
			if (ft_strcmp(curr->key, tmp->key) > 0)
			{
				tmp_key = curr->key;
				tmp_value = curr->value;
				curr->key = tmp->key;
				curr->value = tmp->value;
				tmp->key = tmp_key;
				tmp->value = tmp_value;
			}
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}
