/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_shit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:41:28 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/03 18:53:49 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

void	DEBUG_PRINT_LIST(t_hash *head)
{
	t_hash	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%d %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	DEBUG_PRINT_LIST_2(t_env *head)
{
	t_env	*tmp;
	t_env	*tmp_2;

	tmp = head;
	while (tmp->next != NULL)
	{
		tmp_2 = tmp->next;
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp_2;
	}
	printf("%s =", tmp->key);
	printf("%s\n", tmp->value);
}
