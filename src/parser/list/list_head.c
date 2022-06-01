/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:47:48 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/01 19:28:56 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

t_hash	*ft_lstnew_head(void *key, void *value)
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
