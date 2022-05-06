/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:10:11 by kezekiel          #+#    #+#             */
/*   Updated: 2021/10/11 13:03:57 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst != NULL && lst != NULL)
	{
		tmp = *lst;
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		return ;
	}
	*lst = new;
}
