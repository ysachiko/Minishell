/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:47:48 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/10 18:34:22 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

t_hash	*ft_lstnew_hash(int key, void *value)
{
	t_hash	*new;

	new = malloc(sizeof(t_hash));
	if (new)
	{
		new->key = key;
		new->value = value;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

t_hash	*ft_lstlast_hash(t_hash *lst)
{
	t_hash	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_hash(t_hash **lst, t_hash *new)
{
	t_hash	*tmp;

	if (*lst != NULL && lst != NULL)
	{
		tmp = *lst;
		tmp = ft_lstlast_hash(*lst);
		tmp->next = new;
		new->prev = tmp;
		return ;
	}
	*lst = new;
}
