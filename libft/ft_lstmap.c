/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:09:22 by kezekiel          #+#    #+#             */
/*   Updated: 2021/10/08 15:09:23 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*last;
	t_list	*node;
	void	*content;

	newlist = NULL;
	last = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			if (newlist)
				ft_lstclear(&newlist, del);
			return (NULL);
		}
		if (last)
			last->next = node;
		if (!newlist)
			newlist = node;
		last = node;
		lst = lst->next;
	}
	return (newlist);
}
