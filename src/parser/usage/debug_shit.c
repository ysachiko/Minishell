/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_shit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:41:28 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/02 19:36:51 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

void	DEBUG_PRINT_LIST(t_hash *head)
{
	t_hash	*tmp;
	t_hash	*tmp_2;

	tmp = head;
	while (tmp->next != NULL)
	{
		tmp_2 = tmp->next;
		printf("%s %s\n", tmp->key, tmp->value);
		tmp = tmp_2;
	}
	printf("%s %s\n", tmp->key, tmp->value);
}

void	DEBUG_PRINT_LIST_2(t_env *head)
{
	t_env	*tmp;
	t_env	*tmp_2;

	tmp = head;
	while (tmp->next != NULL)
	{
		tmp_2 = tmp->next;
		printf("%s \n", tmp->arg);
		tmp = tmp_2;
	}
	printf("%s \n", tmp->arg);
}
